/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:43 by edouard           #+#    #+#             */
/*   Updated: 2024/09/29 08:19:24 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int validate_and_open_redirections(t_command *current, t_shell *shell)
{
	t_redir *redir;

	redir = current->redirections;
	while (redir)
	{
		if (open_redirection(redir, shell) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

static void perform_redirections(t_command *current, t_shell *shell)
{
	t_redir *redir;
	t_error_info error_info;

	redir = current->redirections;
	while (redir)
	{
		if (redir->redirection_type == REDIR_IN)
		{
			if (dup2(redir->fd, STDIN_FILENO) == -1)
			{
				error_info = init_error_info(NULL, strerror(errno), 1);
				handle_redirection_error(error_info, shell, redir->fd);
			}
			close(redir->fd);
			redir->fd = -1;
		}
		else
		{
			if (dup2(redir->fd,
						(redir->redirection_type == REDIR_OUT) ? STDOUT_FILENO : STDERR_FILENO) ==
				 -1)
			{
				error_info = init_error_info(NULL, strerror(errno), 1);
				handle_redirection_error(error_info, shell, redir->fd);
			}
			close(redir->fd);
			redir->fd = -1;
		}
		redir = redir->next;
	}
}

static void handle_pipe_redirection(t_command *current)
{
	// Проверяем, есть ли перенаправление на STDOUT
	bool has_stdout_redirection = false;
	t_redir *redir = current->redirections;
	while (redir)
	{
		if (redir->redirection_type == REDIR_OUT || redir->redirection_type == REDIR_APPEND)
		{
			has_stdout_redirection = true;
			break;
		}
		redir = redir->next;
	}

	if (current->next_cmd && !has_stdout_redirection)
	{
		if (dup2(current->shell->pipe_fds[1], STDOUT_FILENO) == -1)
		{
			// Обработка ошибки
		}
		close(current->shell->pipe_fds[0]);
		close(current->shell->pipe_fds[1]);
	}
}

static void handle_prev_fd_redirection(int prev_fd, t_shell *shell)
{
	t_error_info error_info;

	if (prev_fd != 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			error_info = init_error_info(NULL, strerror(errno), 1);
			handle_redirection_error(error_info, shell, prev_fd);
		}
		close(prev_fd);
	}
}

void handle_redirections(t_command *current, int prev_fd)
{
	if (validate_and_open_redirections(current, current->shell) == -1)
	{
		free_shell(current->shell);
		exit(1);
	}
	handle_prev_fd_redirection(prev_fd, current->shell);
	handle_pipe_redirection(current);
	perform_redirections(current, current->shell);
}
