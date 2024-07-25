/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:44:17 by edouard           #+#    #+#             */
/*   Updated: 2024/07/25 12:20:40 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pipe(t_command *current, t_shell *shell)
{
	if (current->next_cmd)
	{
		if (pipe(shell->pipe_fds) == -1)
			ft_exit_error(shell, "pipe failed"); // TODO: handle error
	}
	shell->last_process_id = fork();
	if (shell->last_process_id == -1)
		ft_exit_error(shell, "fork failed"); // TODO: handle error
}

void ft_redirect_input(t_command *current, t_shell *shell, int prev_fd)
{
	if (prev_fd != 0 && shell->input_fd == -2)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			ft_exit_error(shell, "dup2 failed"); // TODO: handle error
		close(prev_fd);
	}
	if (current->next_cmd && shell->output_fd == -2)
	{
		if (dup2(shell->pipe_fds[1], STDOUT_FILENO) == -1)
			ft_exit_error(shell, "dup2 failed"); // TODO: handle error
		if (shell->pipe_fds[0])
			close(shell->pipe_fds[0]); // TODO - check if necessary
		if (shell->pipe_fds[1])
			close(shell->pipe_fds[1]);
	}
}
