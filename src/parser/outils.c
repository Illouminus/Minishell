/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:42:13 by edouard           #+#    #+#             */
/*   Updated: 2024/08/18 17:48:47 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_redirection(t_command *cmd, int type, char *filename)
{
	t_redir *new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
	{
		perror("malloc failed");
		exit(1);
	}

	new_redir->filename = ft_strdup(filename);
	new_redir->redirection_type = type;
	new_redir->next = NULL;
	new_redir->prev = cmd->last_redirection;

	if (cmd->last_redirection)
	{
		cmd->last_redirection->next = new_redir;
	}
	else
	{
		cmd->redirections = new_redir;
	}

	cmd->last_redirection = new_redir;
}