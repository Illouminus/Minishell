/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:42:13 by edouard           #+#    #+#             */
/*   Updated: 2024/08/30 11:28:08 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirection(t_command *cmd, int type, char *filename)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
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
		cmd->redirections = new_redir;
	cmd->last_redirection = new_redir;
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

// Nombre d'arguments depuis la liste de tokens
int	ft_determine_nb_args(t_token *token_list)
{
	int		i;
	t_token	*current_token;

	i = 0;
	current_token = token_list;
	while (current_token->next_tok != NULL
		&& current_token->next_tok->tok_type == TOKEN_TYPE_ARG)
	{
		i++;
		current_token = current_token->next_tok;
	}
	return (i);
}

t_command	*ft_new_command_init(t_command *command, int nb_of_args,
		char *cmd_value_clean, t_shell *shell)
{
	command = malloc(sizeof(t_command));
	if (!command)
	{
		printf("Error in parser, during new_command_init\n");
		return (NULL);
	}
	command->cmd_value = ft_strdup(cmd_value_clean);
	command->cmd_args = malloc((nb_of_args + 1) * sizeof(char *));
	command->is_builtin_cmd = ft_cmd_is_built_in(command->cmd_value);
	command->redir_tokens = NULL;
	command->prev_cmd = NULL;
	command->next_cmd = NULL;
	command->redirections = NULL;
	command->last_redirection = NULL;
	command->shell = shell;
	return (command);
}

char	*ft_clean_token_value(const char *token, int *inside_single_quote)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*cleaned;
	int		inside_double_quote;

	len = ft_strlen(token);
	i = 0;
	j = 0;
	inside_double_quote = 0;
	cleaned = (char *)malloc(len + 1);
	if (!cleaned)
		return (NULL);
	while (token[i])
	{
		if (token[i] == '\'' && !inside_double_quote)
			*inside_single_quote = 1;
		else if (token[i] == '"' && !(*inside_single_quote))
			inside_double_quote = 1;
		else
			cleaned[j++] = token[i];
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}
