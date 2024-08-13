/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/08/13 17:11:05 by adrienhors       ###   ########.fr       */
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

t_command *ft_new_command_init(t_command *command, int nb_of_args, char *cmd_value_clean)
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
	command->input_file = NULL;
	command->output_file = NULL;
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
		printf("  command Input File: %s\n", current_command->input_file);
		printf("  command Output File: %s\n", current_command->output_file);
		printf("  command args: %s\n", current_command->cmd_args[0]);
		printf("  command args: %s\n", current_command->cmd_args[1]);
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
	// printf("Nb of args : %d\n", i);
	return (i);
}

// Gestion des guillemets dans les value des tokens | Value propre prête à envoyer à la création de commandes
char *ft_clean_token_value(const char *token)
{
    size_t len = ft_strlen(token);
    size_t i = 0;
    size_t j = 0;
    int inside_single_quote = 0;
    int inside_double_quote = 0;

    // Allouer une nouvelle chaîne pour stocker le résultat (taille maximale = len)
    char *cleaned = (char *)malloc(len + 1);
    if (!cleaned)
    {
        return NULL; // Gestion de l'erreur si l'allocation échoue
    }

    // Parcourir chaque caractère de la chaîne d'entrée
    while (i < len)
    {
        if (token[i] == '\'' && !inside_double_quote)
        {
            inside_single_quote = !inside_single_quote; // Alterne l'état des guillemets simples
        }
        else if (token[i] == '"' && !inside_single_quote)
        {
            inside_double_quote = !inside_double_quote; // Alterne l'état des guillemets doubles
        }
        else
        {
            cleaned[j] = token[i];
            j++;
        }
        i++;
    }

    // Ajouter le caractère nul de fin
    cleaned[j] = '\0';

    return cleaned;
}



// Identfy commands and their arguments. Recognitiion of operators and pipes. Build an AST at the end
int parser(t_shell *shell)
{
	t_token *current_token;
	t_command *new_command;
	t_command *last_command;
	char *cmd_value_clean;
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
			cmd_value_clean = ft_clean_token_value(current_token->tok_value);
			if (current_token->tok_type == TOKEN_TYPE_CMD)
			{
				cmd_nb_args = ft_determine_nb_args(current_token);
				i = 0;
				new_command = ft_new_command_init(new_command, cmd_nb_args, cmd_value_clean);
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
			else if (current_token->tok_type == TOKEN_TYPE_REDIR_IN || current_token->tok_type == TOKEN_TYPE_REDIR_OUT)
			{
				if (current_token->tok_type == TOKEN_TYPE_REDIR_IN)
				{
					last_command->input_file = ft_expander(ft_clean_token_value(current_token->next_tok->tok_value), shell);
				}
				else if (current_token->tok_type == TOKEN_TYPE_REDIR_OUT)
				{
					last_command->output_file = ft_expander(ft_clean_token_value(current_token->next_tok->tok_value), shell);
				}
			}
			else if (current_token->tok_type == TOKEN_TYPE_ARG && (current_token->prev_tok->tok_type != TOKEN_TYPE_REDIR_IN && current_token->prev_tok->tok_type != TOKEN_TYPE_REDIR_OUT))
			{
				last_command->cmd_args[i] = ft_expander(cmd_value_clean, shell);
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