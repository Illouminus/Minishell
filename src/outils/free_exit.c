/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:15:23 by edouard           #+#    #+#             */
/*   Updated: 2024/08/30 13:41:40 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_redirections(t_redir **redir)
{
	t_redir *temp;

	while (*redir)
	{
		temp = *redir;
		*redir = (*redir)->next;

		if (temp->filename && ft_strcmp(temp->filename, "minishell_heredoc") == 0)
		{
			unlink(temp->filename);
		}
		free(temp->filename);
		free(temp);
	}
	*redir = NULL;
}

static void free_commands(t_command **command_list)
{
	t_command *cmd_temp;
	while (*command_list)
	{
		cmd_temp = *command_list;
		*command_list = (*command_list)->next_cmd;
		free(cmd_temp->cmd_value);
		if (cmd_temp->cmd_args)
		{
			char **args = cmd_temp->cmd_args;
			while (*args)
			{
				free(*args);
				args++;
			}
			free(cmd_temp->cmd_args);
		}
		if (cmd_temp->redirections)
			free_redirections(&cmd_temp->redirections);
		free(cmd_temp);
	}
	*command_list = NULL;
}

static void free_tokens(t_token **token_list)
{
	t_token *tok_temp;
	while (*token_list)
	{
		tok_temp = *token_list;
		*token_list = (*token_list)->next_tok;
		free(tok_temp->tok_value);
		free(tok_temp);
	}
	*token_list = NULL;
}

void free_shell(t_shell *shell)
{
	if (!shell)
		return;
	if (shell->command_list)
		free_commands(&shell->command_list);
	if (shell->token_list)
		free_tokens(&shell->token_list);
}
