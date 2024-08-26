/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/08/26 16:04:26 by adrienhors       ###   ########.fr       */
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
	size_t len; 
	size_t i; 
	size_t j; 
	char *cleaned;
	int inside_double_quote;

	len = ft_strlen(token);
	i = 0; 
	j = 0; 
	inside_double_quote = 0;
	cleaned = (char *)malloc(len + 1);
	if (!cleaned)
		return NULL;
	while (i < len)
	{
		if (token[i] == '\'' && !inside_double_quote)
			*inside_single_quote = 1;
		else if (token[i] == '"' && !(*inside_single_quote))
			inside_double_quote = 1;
		else
		{
			cleaned[j] = token[i];
			j++;
		}
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}

void ft_parser_handle_redirection(t_token **current_token, t_shell *shell, t_command *last_command, int *inside_single_quote) 
{
    char *file_name;

    if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_IN) {
        file_name = ft_expander(ft_clean_token_value((*current_token)->next_tok->tok_value, inside_single_quote), shell, *inside_single_quote);
        add_redirection(last_command, REDIR_IN, file_name);
    }
    else if ((*current_token)->tok_type == TOKEN_TYPE_HEREDOC) {
        *current_token = (*current_token)->next_tok->next_tok;
        file_name = ft_heredoc_handler((*current_token)->tok_value);
        add_redirection(last_command, REDIR_IN, file_name);
    }
    else if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_OUT) {
        file_name = ft_expander(ft_clean_token_value((*current_token)->next_tok->tok_value, inside_single_quote), shell, *inside_single_quote);
        add_redirection(last_command, REDIR_OUT, file_name);
    }
    else if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_APPEND) {
        *current_token = (*current_token)->next_tok;
        file_name = ft_expander(ft_clean_token_value((*current_token)->next_tok->tok_value, inside_single_quote), shell, *inside_single_quote);
        add_redirection(last_command, REDIR_APPEND, file_name);
    }
}

void ft_parser_handle_command(t_token *current_token, char *cmd_value_clean, t_shell *shell, t_command **last_command) 
{
    int cmd_nb_args;
    t_command *new_command;

	new_command = NULL; 
    // Déterminer le nombre d'arguments pour la commande actuelle
    cmd_nb_args = ft_determine_nb_args(current_token);
    
    // Initialiser la nouvelle commande
    new_command = ft_new_command_init(new_command, cmd_nb_args, cmd_value_clean, shell);
    // Si une commande précédente existe, on la relie à la nouvelle
    if (*last_command) 
	{
        (*last_command)->next_cmd = new_command;
        new_command->prev_cmd = *last_command;
    } 
	else 
        shell->command_list = new_command;
    // Mettre à jour le pointeur de la dernière commande
    *last_command = new_command;
}

// Déclaration de la nouvelle fonction
int ft_parser_handle_empty_command(char *cmd_value_clean, t_token **current_token) 
{
    if (*cmd_value_clean == '\0' && (*current_token)->next_tok) {
        *current_token = (*current_token)->next_tok;
        (*current_token)->tok_type = TOKEN_TYPE_CMD;
        return 1;  // Indique qu'on doit continuer avec le prochain token
    }
    return 0;  // Indique qu'on ne doit pas sauter de token
}


int ft_check_user_input(t_shell *shell) {
    if (!shell->user_input || ft_strcmp(shell->user_input, "/0") == 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

// Identfy commands and their arguments. Recognitiion of operators and pipes. Build an AST at the end
int parser(t_shell *shell)
{
	t_token *current_token;
	t_command *last_command;
	char *cmd_value_clean;
	int i;

	last_command = NULL;
	current_token = shell->token_list;
	if (ft_check_user_input(shell) == EXIT_FAILURE)
        return (EXIT_FAILURE);
	while (current_token)
	{
		int inside_single_quote = 0;
		cmd_value_clean = ft_expander(ft_clean_token_value(current_token->tok_value, &inside_single_quote), shell, inside_single_quote);
		if (ft_parser_handle_empty_command(cmd_value_clean, &current_token))
			continue;
		if (current_token->tok_type == TOKEN_TYPE_CMD) 
		{
			ft_parser_handle_command(current_token, cmd_value_clean, shell, &last_command);
			i = 0;
		} 
		else if (current_token->tok_type == TOKEN_TYPE_REDIR_IN || current_token->tok_type == TOKEN_TYPE_REDIR_OUT || current_token->tok_type == TOKEN_TYPE_REDIR_APPEND || current_token->tok_type == TOKEN_TYPE_HEREDOC)
			ft_parser_handle_redirection(&current_token, shell, last_command, &inside_single_quote); 
		else if (current_token->tok_type == TOKEN_TYPE_ARG && (current_token->prev_tok->tok_type != TOKEN_TYPE_REDIR_IN && current_token->prev_tok->tok_type != TOKEN_TYPE_REDIR_OUT))
		{
			last_command->cmd_args[i] = ft_expander(cmd_value_clean, shell, inside_single_quote);
			i++;
		}
		current_token = current_token->next_tok;
	}
	if (last_command && last_command->cmd_args)
		last_command->cmd_args[i] = NULL;
	return (EXIT_SUCCESS);
}
