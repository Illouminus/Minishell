/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:15:23 by edouard           #+#    #+#             */
/*   Updated: 2024/09/30 10:38:14 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirections(t_redir **redir)
{
	t_redir	*temp;

	while (*redir)
	{
		temp = *redir;
		*redir = (*redir)->next;
		if (temp->filename && ft_strncmp(temp->filename,
				"/tmp/minishell_heredoc_", 21) == 0)
			unlink(temp->filename);
		if (temp->filename)
		{
			free(temp->filename);
			temp->filename = NULL;
		}
		if (temp->fd != -1)
		{
			close(temp->fd);
			temp->fd = -1;
		}
		free(temp);
		temp = NULL;
	}
	*redir = NULL;
}

static void	free_command_args(char **cmd_args)
{
	char	**args;

	if (cmd_args)
	{
		args = cmd_args;
		while (*args)
		{
			if (*args)
				free(*args);
			*args = NULL;
			args++;
		}
		free(cmd_args);
		cmd_args = NULL;
	}
	return ;
}

static void	free_commands(t_command **command_list)
{
	t_command	*cmd_temp;

	if (!command_list)
		return ;
	while (*command_list)
	{
		cmd_temp = *command_list;
		*command_list = (*command_list)->next_cmd;
		if (cmd_temp->cmd_value)
		{
			free(cmd_temp->cmd_value);
			cmd_temp->cmd_value = NULL;
		}
		if (cmd_temp->cmd_args)
			free_command_args(cmd_temp->cmd_args);
		if (cmd_temp->redirections)
			free_redirections(&cmd_temp->redirections);
		free(cmd_temp);
		cmd_temp = NULL;
	}
	*command_list = NULL;
}

static void	free_tokens(t_token **token_list)
{
	t_token	*tok_temp;

	while (*token_list)
	{
		tok_temp = *token_list;
		*token_list = (*token_list)->next_tok;
		if (tok_temp->tok_value)
		{
			free(tok_temp->tok_value);
			tok_temp->tok_value = NULL;
		}
		free(tok_temp);
		tok_temp = NULL;
	}
	*token_list = NULL;
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->command_list)
		free_commands(&shell->command_list);
	if (shell->token_list)
		free_tokens(&shell->token_list);
	if (shell->pipe_fds[0] != -2)
		close(shell->pipe_fds[0]);
	if (shell->pipe_fds[1] != -2)
		close(shell->pipe_fds[1]);
	if (shell->temp_stdin != -1)
		close(shell->temp_stdin);
}
