/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/08/18 18:33:17 by edouard          ###   ########.fr       */
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

t_command *ft_new_command_init(t_command *command, int nb_of_args, char *cmd_value_clean, t_shell *shell)
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
		printf("  command args: %s\n", current_command->cmd_args[0]);
		printf("  command args: %s\n", current_command->cmd_args[1]);
		current_command = current_command->next_cmd;
		index++;
	}
}
/*
void handle_error_parser(const char *cmd, const char *error_message, int exit_code, t_shell *shell)
{
	fprintf(stderr, "minishell: %s: %s\n", cmd, error_message);
	shell->last_exit_status = exit_code;
	// free_shell(shell);
	//  ßexit(shell->last_exit_status);
}

static int ft_check_input_file(char *file_path, t_shell *shell)
{
	struct stat path_stat;

	if (stat(file_path, &path_stat) == -1)
	{
		handle_error_parser(file_path, "No such file or directory", 1, shell);
		return 1;
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		handle_error_parser(file_path, "Is a directory", 1, shell);
		return 1;
	}
	if (access(file_path, R_OK) == -1)
	{
		handle_error_parser(file_path, "Permission denied", 1, shell);
		return 1;
	}
	return 0;
}
*/

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
char *ft_clean_token_value(const char *token, int *inside_single_quote)
{
	size_t len = ft_strlen(token);
	size_t i = 0;
	size_t j = 0;
	int inside_double_quote = 0;

	char *cleaned = (char *)malloc(len + 1);
	if (!cleaned)
	{
		return NULL;
	}

	while (i < len)
	{
		if (token[i] == '\'' && !inside_double_quote)
		{
			*inside_single_quote = 1;
		}
		else if (token[i] == '"' && !(*inside_single_quote))
		{
			inside_double_quote = 1;
		}
		else
		{
			cleaned[j] = token[i];
			j++;
		}
		i++;
	}

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
			int inside_single_quote = 0;
			cmd_value_clean = ft_clean_token_value(current_token->tok_value, &inside_single_quote);
			if (current_token->tok_type == TOKEN_TYPE_CMD)
			{
				cmd_nb_args = ft_determine_nb_args(current_token);
				i = 0;
				new_command = ft_new_command_init(new_command, cmd_nb_args, cmd_value_clean, shell);
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
			else if (current_token->tok_type == TOKEN_TYPE_REDIR_IN || current_token->tok_type == TOKEN_TYPE_REDIR_OUT || current_token->tok_type == TOKEN_TYPE_REDIR_APPEND)
			{
				if (current_token->tok_type == TOKEN_TYPE_REDIR_IN)
				{
					char *input_file = ft_expander(ft_clean_token_value(current_token->next_tok->tok_value, &inside_single_quote), shell, inside_single_quote);
					add_redirection(last_command, REDIR_IN, input_file);
				}
				else if (current_token->tok_type == TOKEN_TYPE_REDIR_OUT)
				{
					char *output_file = ft_expander(ft_clean_token_value(current_token->next_tok->tok_value, &inside_single_quote), shell, inside_single_quote);
					add_redirection(last_command, REDIR_OUT, output_file);
				}
				else if (current_token->tok_type == TOKEN_TYPE_REDIR_APPEND)
				{
					current_token = current_token->next_tok;
					char *output_file_append = ft_expander(ft_clean_token_value(current_token->next_tok->tok_value, &inside_single_quote), shell, inside_single_quote);
					add_redirection(last_command, REDIR_APPEND, output_file_append);
				}
			}
			else if (current_token->tok_type == TOKEN_TYPE_ARG && (current_token->prev_tok->tok_type != TOKEN_TYPE_REDIR_IN && current_token->prev_tok->tok_type != TOKEN_TYPE_REDIR_OUT))
			{
				last_command->cmd_args[i] = ft_expander(cmd_value_clean, shell, inside_single_quote);
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