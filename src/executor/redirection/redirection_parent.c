/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:55:08 by edouard           #+#    #+#             */
/*   Updated: 2024/09/28 18:07:25 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redir_in_exec(t_redir *redir)
{
	redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		return -1;
	}

	if (dup2(redir->fd, STDIN_FILENO) == -1)
	{
		perror("dup2 failed for REDIR_IN");
		close(redir->fd);
		return -1;
	}

	close(redir->fd);
	return 0;
}

int handle_redir_out_exec(t_redir *redir)
{
	redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		return -1;
	}

	if (dup2(redir->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed for REDIR_OUT");
		close(redir->fd);
		return -1;
	}
	close(redir->fd);
	return 0;
}

int handle_redir_append_exec(t_redir *redir)
{
	redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		return -1;
	}

	if (dup2(redir->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed for REDIR_APPEND");
		close(redir->fd);
		return -1;
	}
	close(redir->fd);
	return 0;
}

int apply_redirections(t_redir *redir)
{
	while (redir)
	{
		if (redir->redirection_type == REDIR_IN)
		{
			if (handle_redir_in_exec(redir) != 0)
				return -1;
		}
		else if (redir->redirection_type == REDIR_OUT)
		{
			if (handle_redir_out_exec(redir) != 0)
				return -1;
		}
		else if (redir->redirection_type == REDIR_APPEND)
		{
			if (handle_redir_append_exec(redir) != 0)
				return -1;
		}
		redir = redir->next;
	}
	return 0;
}

void handle_builtin_with_redirections(t_command *cmd, t_shell *shell)
{
	int saved_stdin;
	int saved_stdout;

	if(cmd->redirections == NULL)
	{
		ft_exec_builtins(cmd, shell, true);
		return;
	}
	if (save_standard_fds(&saved_stdin, &saved_stdout) != 0)
		return;
	if (apply_redirections(cmd->redirections) != 0)
	{
		restore_standard_fds(saved_stdin, saved_stdout);
		return;
	}

	ft_exec_builtins(cmd, shell, true);

	if (restore_standard_fds(saved_stdin, saved_stdout) != 0)
		return;
}