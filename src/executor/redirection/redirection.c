/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:43 by edouard           #+#    #+#             */
/*   Updated: 2024/08/14 09:36:08 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_file_access(const char *filepath, int mode)
{
	struct stat file_stat;

	if (access(filepath, mode) == -1)
	{
		perror("Access error");
		return -1;
	}

	if (stat(filepath, &file_stat) == -1)
	{
		perror("Stat error");
		return -1;
	}
	if (S_ISDIR(file_stat.st_mode))
	{
		fprintf(stderr, "Error: '%s' is a directory\n", filepath);
		return -1;
	}

	return 0; // Все проверки прошли успешно
}

static void handle_input_redirection(const char *input_file, t_shell *shell)
{
	int input_fd;

	if (input_file)
	{
		if (check_file_access(input_file, R_OK) == -1)
		{
			free_shell(shell);

			exit(1);
			return; // Если файл недоступен или это директория, выходим
		}
		input_fd = open(input_file, O_RDONLY);
		if (input_fd == -1)
		{
			free_shell(shell);
			exit(1);
			perror("failed to open input file");
			return; // TODO: handle error properly
		}
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for input");
			close(input_fd);
			return; // TODO: handle error properly
		}
		close(input_fd);
	}
}

static void handle_output_redirection(const char *output_file, t_shell *shell)
{
	int output_fd;

	if (output_file)
	{
		if (access(output_file, F_OK) == 0 && check_file_access(output_file, W_OK) == -1)
		{
			free_shell(shell);
			exit(1);
			return; // Если файл недоступен или это директория, выходим
		}
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
		{
			free_shell(shell);
			exit(1);
			perror("failed to open output file");
			return; // TODO: handle error properly
		}
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for output");
			close(output_fd);
			return; // TODO: handle error properly
		}
		close(output_fd);
	}
}

static void handle_pipe_redirection(t_command *current)
{
	if (current->next_cmd)
	{
		if (dup2(current->pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for pipe_fds[1]");
			close(current->pipe_fds[0]);
			close(current->pipe_fds[1]);
			return; // TODO: handle error properly
		}
		close(current->pipe_fds[0]);
		close(current->pipe_fds[1]);
	}
}

static void handle_prev_fd_redirection(int prev_fd)
{
	if (prev_fd != 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for pipe input");
			close(prev_fd);
			return; // TODO: handle error properly
		}
		close(prev_fd);
	}
}

void handle_redirections(t_command *current, int prev_fd)
{
	handle_input_redirection(current->input_file, current->shell);
	handle_output_redirection(current->output_file, current->shell);
	handle_pipe_redirection(current);
	handle_prev_fd_redirection(prev_fd);
}