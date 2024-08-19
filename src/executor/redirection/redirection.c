/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:43 by edouard           #+#    #+#             */
/*   Updated: 2024/08/19 08:57:33 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_redirection_error(const char *filepath, const char *error_message, int exit_code, t_shell *shell, int fd)
{
	if (fd != -1)
		close(fd);
	fprintf(stderr, "minishell: %s: %s\n", filepath, error_message);
	shell->last_exit_status = exit_code;
	free_shell(shell);
	exit(exit_code);
}

static int check_and_open_file(const char *filepath, int flags, mode_t mode, t_shell *shell)
{
	int fd;
	struct stat file_stat;

	if (access(filepath, F_OK) == 0)
	{
		if (stat(filepath, &file_stat) == -1)
		{
			handle_redirection_error(filepath, strerror(errno), 1, shell, -1);
			return -1;
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			handle_redirection_error(filepath, "Is a directory", 126, shell, -1);
			return -1;
		}
		if ((flags & O_WRONLY) && access(filepath, W_OK) == -1)
		{
			handle_redirection_error(filepath, strerror(errno), 1, shell, -1);
			return -1;
		}
	}
	else if (!(flags & O_WRONLY))
	{
		handle_redirection_error(filepath, "No such file or directory", 1, shell, -1);
		return -1;
	}

	fd = open(filepath, flags, mode);
	if (fd == -1)
	{
		handle_redirection_error(filepath, strerror(errno), 1, shell, fd);
		return -1;
	}
	return fd;
}

static int validate_and_open_redirections(t_command *current, t_shell *shell, int *input_fd, int *output_fd)
{
	t_redir *redir = current->redirections;

	while (redir)
	{
		if (redir->redirection_type == REDIR_IN)
		{
			*input_fd = check_and_open_file(redir->filename, O_RDONLY, 0, shell);
			if (*input_fd == -1)
				return -1;
		}
		else if (redir->redirection_type == REDIR_OUT)
		{
			*output_fd = check_and_open_file(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644, shell);
			if (*output_fd == -1)
				return -1;
		}
		else if (redir->redirection_type == REDIR_APPEND)
		{
			*output_fd = check_and_open_file(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644, shell);
			if (*output_fd == -1)
				return -1;
		}
		redir = redir->next;
	}
	return 0;
}

static void perform_redirections(int input_fd, int output_fd, t_shell *shell)
{
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			handle_redirection_error(NULL, strerror(errno), 1, shell, input_fd);
		}
		close(input_fd);
	}
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			handle_redirection_error(NULL, strerror(errno), 1, shell, output_fd);
		}
		close(output_fd);
	}
}

static void handle_pipe_redirection(t_command *current)
{
	if (current->next_cmd)
	{
		if (dup2(current->shell->pipe_fds[1], STDOUT_FILENO) == -1)
		{
			handle_redirection_error(NULL, strerror(errno), 1, current->shell, -1);
		}
		close(current->shell->pipe_fds[0]);
		close(current->shell->pipe_fds[1]);
	}
}

static void handle_prev_fd_redirection(int prev_fd, t_shell *shell)
{
	if (prev_fd != 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			handle_redirection_error(NULL, strerror(errno), 1, shell, prev_fd);
		}
		close(prev_fd);
	}
}

void handle_redirections(t_command *current, int prev_fd)
{
	int input_fd = -1;
	int output_fd = -1;

	if (validate_and_open_redirections(current, current->shell, &input_fd, &output_fd) == -1)
	{
		free_shell(current->shell);
		exit(1);
	}

	handle_prev_fd_redirection(prev_fd, current->shell);
	handle_pipe_redirection(current);

	perform_redirections(input_fd, output_fd, current->shell);
