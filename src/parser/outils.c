/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:42:13 by edouard           #+#    #+#             */
/*   Updated: 2024/09/27 16:22:34 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirection(t_command **cmd_ptr, int type, char *filename)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->filename = ft_strdup(filename);
	if (!new_redir->filename)
		return ;
	new_redir->redirection_type = type;
	new_redir->next = NULL;
	new_redir->prev = (*cmd_ptr)->last_redirection;
	if ((*cmd_ptr)->last_redirection)
	{
		(*cmd_ptr)->last_redirection->next = new_redir;
	}
	else
	{
		(*cmd_ptr)->redirections = new_redir;
	}
	(*cmd_ptr)->last_redirection = new_redir;
}

int	ft_cmd_is_built_in(char *value)
{
	if (ft_strcmp(value, "cd") == 0)
		return (1);
	else if (ft_strcmp(value, "echo") == 0)
		return (1);
	else if (ft_strcmp(value, "env") == 0)
		return (1);
	else if (ft_strcmp(value, "exit") == 0)
		return (1);
	else if (ft_strcmp(value, "export") == 0)
		return (1);
	else if (ft_strcmp(value, "pwd") == 0)
		return (1);
	else if (ft_strcmp(value, "unset") == 0)
		return (1);
	return (0);
}

int	ft_determine_nb_args(t_token *token_list)
{
	int		count;
	t_token	*current_token;

	count = 0;
	current_token = token_list;
	while (current_token != NULL)
	{
		if (current_token->tok_type == TOKEN_TYPE_ARG)
			count++;
		current_token = current_token->next_tok;
	}
	return (count);
}

t_command	*ft_new_command_init(t_command *command, int nb_of_args,
		char *cmd_value_clean, t_shell *shell)
{
	int	i;

	i = 0;
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd_value = ft_strdup(cmd_value_clean);
	command->cmd_args = malloc((nb_of_args + 1) * sizeof(char *));
	if (nb_of_args == 0)
		command->cmd_args[0] = NULL;
	while (i < nb_of_args)
	{
		command->cmd_args[i] = NULL;
		i++;
	}
	command->cmd_args[nb_of_args] = NULL;
	command->is_builtin_cmd = ft_cmd_is_built_in(command->cmd_value);
	command->prev_cmd = NULL;
	command->next_cmd = NULL;
	command->redirections = NULL;
	command->last_redirection = NULL;
	command->shell = shell;
	return (command);
}
