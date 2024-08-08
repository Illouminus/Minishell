/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/08/08 14:46:45 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cmd_is_built_in(char *value)
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

t_command *ft_new_command_init(t_command *command, t_token *current_token, int nb_of_args)
{
	command = malloc(sizeof(t_command));
	if (!command)
	{
		printf("Error in parser, during new_command_init\n");
		return (NULL);
	}
	command->cmd_value = ft_strdup(current_token->tok_value);
	command->cmd_args = malloc((nb_of_args + 1) * sizeof(char *));
	command->is_builtin_cmd = ft_cmd_is_built_in(command->cmd_value);
	command->redir_tokens = NULL;
	command->prev_cmd = NULL;
	command->next_cmd = NULL;
	command->output_file = NULL;
	command->input_file = NULL;
	return (command);
}

void ft_afficher_cmd_args(char **cmd_args, int len)
{
	int i;

	if (cmd_args == NULL)
	{
		printf("Le tableau est vide.\n");
		return;
	}

	i = 0;
	while (i < len)
	{
		printf("cmd_args[%d]: %s\n", i, cmd_args[i]);
		i++;
	}
}

// Fonction pour afficher une liste de commandes
void ft_afficher_command_list(t_command *command_list)
{
	t_command *current_command;
	int index;

	index = 0;
	current_command = command_list;
	while (current_command)
	{
		printf("Commande numéro %d:\n", index);
		printf("  cmd_value: %s\n", current_command->cmd_value);
		printf("  is_builtin_cmd: %s\n", current_command->is_builtin_cmd ? "true" : "false");
		current_command = current_command->next_cmd;
		index++;
	}
}

// Nombre d'arguments depuis la liste de tokens
int ft_determine_nb_args(t_token *token_list)
{
	int i;
	t_token *current_token;

	i = 0;
	current_token = token_list;
	while (current_token->next_tok != NULL && current_token->next_tok->tok_type == TOKEN_TYPE_ARG)
	{
		i++;
		current_token = current_token->next_tok;
	}
	return (i);
}

// Identfy commands and their arguments. Recognitiion of operators and pipes. Build an AST at the end
int parser(t_shell *shell)
{
	t_token *current_token;
	t_command *new_command;
	t_command *last_command;
	int cmd_nb_args;
	int i;

	last_command = NULL;
	current_token = shell->token_list;
	if (!shell->user_input)
		return (EXIT_FAILURE);
	else if (ft_strcmp(shell->user_input, "/0") == 0)
		return (EXIT_FAILURE);
	else
	{
		while (current_token)
		{
			if (current_token->tok_type == TOKEN_TYPE_CMD)
			{
				cmd_nb_args = ft_determine_nb_args(current_token);
				i = 0; // On mets i à 0 pour le tableau d'args de la commande
				new_command = ft_new_command_init(new_command, current_token, cmd_nb_args);
				if (last_command)
				{
					last_command->next_cmd = new_command;
					new_command->prev_cmd = last_command;
				}
				else
				{
					shell->command_list = new_command;
				}
				last_command = new_command;
			}
			else if (current_token->tok_type == TOKEN_TYPE_ARG)
			{
				last_command->cmd_args[i] = ft_strdup(current_token->tok_value);
				i++;
			}
			current_token = current_token->next_tok;
		}
		// ft_afficher_command_list(shell->command_list);
	}
	if (last_command && last_command->cmd_args)
		last_command->cmd_args[i] = NULL;
	return (EXIT_SUCCESS);
}