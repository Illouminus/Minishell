/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:43 by edouard           #+#    #+#             */
/*   Updated: 2024/08/18 18:01:15 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_file_access(const char *filepath, int mode, t_shell *shell)
{
	struct stat file_stat;

	if (access(filepath, mode) == -1)
	{
		perror("Access error");
		shell->last_exit_status = 1;
		return -1;
	}

	if (stat(filepath, &file_stat) == -1)
	{
		perror("Stat error");
		shell->last_exit_status = 1;
		return -1;
	}
	if (S_ISDIR(file_stat.st_mode))
	{
		fprintf(stderr, "Error: '%s' is a directory\n", filepath);
		shell->last_exit_status = 1;
		return -1;
	}

	return 0; // Все проверки прошли успешно
}

static int validate_redirections(t_command *current, t_shell *shell)
{
	t_redir *redir = current->redirections;

	while (redir)
	{
		if (redir->redirection_type == REDIR_IN && check_file_access(redir->filename, R_OK, shell) == -1)
			return -1;
		if ((redir->redirection_type == REDIR_OUT || redir->redirection_type == REDIR_APPEND) &&
			 (access(redir->filename, F_OK) == 0 && check_file_access(redir->filename, W_OK, shell) == -1))
			return -1;
		redir = redir->next;
	}

	return 0; // Все проверки прошли успешно
}

static void perform_redirections(t_command *current, t_shell *shell)
{
	t_redir *redir = current->redirections;
	int fd;

	while (redir)
	{
		if (redir->redirection_type == REDIR_IN)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd == -1)
			{
				perror("failed to open input file");
				shell->last_exit_status = 1;
				free_shell(shell);
				exit(1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2 failed for input");
				close(fd);
				free_shell(shell);
				exit(1);
			}
			close(fd);
		}
		else if (redir->redirection_type == REDIR_OUT)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("failed to open output file");
				shell->last_exit_status = 1;
				free_shell(shell);
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 failed for output");
				close(fd);
				free_shell(shell);
				exit(1);
			}
			close(fd);
		}
		else if (redir->redirection_type == REDIR_APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("failed to open output file");
				shell->last_exit_status = 1;
				free_shell(shell);
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 failed for output");
				close(fd);
				free_shell(shell);
				exit(1);
			}
			close(fd);
		}
		redir = redir->next;
	}
}

static void handle_pipe_redirection(t_command *current)
{
	if (current->next_cmd)
	{
		if (dup2(current->shell->pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for pipe_fds[1]");
			close(current->shell->pipe_fds[0]);
			close(current->shell->pipe_fds[1]);
			exit(1);
		}
		close(current->shell->pipe_fds[0]);
		close(current->shell->pipe_fds[1]);
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
			exit(1);
		}
		close(prev_fd);
	}
}

void handle_redirections(t_command *current, int prev_fd)
{
	if (validate_redirections(current, current->shell) == -1)
	{
		free_shell(current->shell);
		exit(1);
	}

	handle_prev_fd_redirection(prev_fd);
	handle_pipe_redirection(current);
	perform_redirections(current, current->shell);
}