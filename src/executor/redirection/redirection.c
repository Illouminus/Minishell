/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:43 by edouard           #+#    #+#             */
/*   Updated: 2024/09/30 10:47:37 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input_redirections(t_command *current, t_shell *shell)
{
	t_redir			*redir;
	t_error_info	error_info;

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
		redir = redir->next;
	}
}

static void	handle_output_redirections(t_command *current, t_shell *shell)
{
	t_redir			*redir;
	t_error_info	error_info;

	redir = current->redirections;
	while (redir)
	{
		if (redir->redirection_type == REDIR_OUT
			|| redir->redirection_type == REDIR_APPEND)
		{
			if (dup2(redir->fd, STDOUT_FILENO) == -1)
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

static void	handle_pipe_redirection(t_command *current)
{
	bool	has_stdout_redirection;
	t_redir	*redir;

	has_stdout_redirection = false;
	redir = current->redirections;
	while (redir)
	{
		if (redir->redirection_type == REDIR_OUT
			|| redir->redirection_type == REDIR_APPEND)
		{
			has_stdout_redirection = true;
			break ;
		}
		redir = redir->next;
	}
	if (current->next_cmd)
	{
		if (!has_stdout_redirection)
			dup2(current->shell->pipe_fds[1], STDOUT_FILENO);
		if (current->shell->pipe_fds[0] != -2)
			close(current->shell->pipe_fds[0]);
		if (current->shell->pipe_fds[1] != -2)
			close(current->shell->pipe_fds[1]);
	}
}

static void	handle_prev_fd_redirection(int prev_fd, t_shell *shell)
{
	t_error_info	error_info;

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

void	handle_redirections(t_command *current, int prev_fd)
{
	if (validate_and_open_redirections(current, current->shell) == -1)
	{
		free_shell(current->shell);
		exit(1);
	}
	handle_prev_fd_redirection(prev_fd, current->shell);
	handle_pipe_redirection(current);
	handle_input_redirections(current, current->shell);
	handle_output_redirections(current, current->shell);
}
