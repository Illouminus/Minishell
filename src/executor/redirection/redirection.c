/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:43 by edouard           #+#    #+#             */
/*   Updated: 2024/09/27 14:50:53 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_and_open_redirections(t_command *current, t_shell *shell,
		int *input_fd, int *output_fd)
{
	t_redir	*redir;

	redir = current->redirections;
	while (redir)
	{
		if (redir->redirection_type == REDIR_IN)
		{
			if (open_redirection(redir, input_fd, shell) == -1)
				return (-1);
		}
		else
		{
			if (open_redirection(redir, output_fd, shell) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

static void	perform_redirections(int input_fd, int output_fd, t_shell *shell)
{
	t_error_info	error_info;

	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			error_info = init_error_info(NULL, strerror(errno), 1);
			handle_redirection_error(error_info, shell, input_fd);
		}
		close(input_fd);
	}
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			error_info = init_error_info(NULL, strerror(errno), 1);
			handle_redirection_error(error_info, shell, output_fd);
		}
		close(output_fd);
	}
}

static void	handle_pipe_redirection(t_command *current)
{
	t_error_info	error_info;

	if (current->next_cmd)
	{
		if (dup2(current->shell->pipe_fds[1], STDOUT_FILENO) == -1)
		{
			error_info = init_error_info(NULL, strerror(errno), 1);
			handle_redirection_error(error_info, current->shell, -1);
		}
		close(current->shell->pipe_fds[0]);
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
	int	input_fd;
	int	output_fd;

	input_fd = -1;
	output_fd = -1;
	if (validate_and_open_redirections(current, current->shell, &input_fd,
			&output_fd) == -1)
	{
		free_shell(current->shell);
		exit(1);
	}
	handle_prev_fd_redirection(prev_fd, current->shell);
	handle_pipe_redirection(current);
	perform_redirections(input_fd, output_fd, current->shell);
	if (current->shell->temp_stdin != -1)
	{
		close(current->shell->temp_stdin);
		current->shell->temp_stdin = -1;
	}
}
