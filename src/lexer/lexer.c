/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:38:33 by edouard           #+#    #+#             */
/*   Updated: 2024/08/07 12:28:33 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction d'affichage temporaire | A supprimer plus tard
void ft_print_tokens(t_token *token_list)
{
	t_token *current = token_list;
	printf("RÉSULTAT DU LEXER\n");
	while (current != NULL)
	{

		printf("Token: %s, Type: %d\n", current->tok_value, current->tok_type);
		current = current->next_tok;
	}
	printf("\n\n");
}

// Fonction principale de tokenisation
void ft_tokenize_input(char *input, t_shell *shell)
{
	int i;
	int start;
	char quote_char;
	t_token_type type;
	int is_first_token;
	char *token_value;

	i = 0;
	start = 0;
	quote_char = '\0';
	is_first_token = 1;
	while (input[i])
	{
		// Skip whitespace
		i = ft_skip_whitespace(input, i);
		if (input[i] == '\0')
			break;
		start = i;
		// Handle quotes
		if (input[i] == '"' || input[i] == '\'')
		{
			i = ft_handle_quotes(input, i, &quote_char);
			if (i == -1)
				return; // A corresponding closing quote was not found
		}
		else
		{
			// Check for special characters
			if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			{
				// If it's a special character, we treat it as a separate token
				i++;
			}
			else
			{
				// Regular token parsing
				while (input[i] != '\0' && !ft_isspace(input[i]) && input[i] != '"' && input[i] != '\'' && input[i] != '|' && input[i] != '<' && input[i] != '>')
					i++;
			}
		}
		// Determine the type of the token
		type = ft_determine_token_type(input, start, is_first_token);
		if (type == TOKEN_TYPE_PIPE)
			is_first_token = 1;
		else
			is_first_token = 0;

		// Create and add the token
		token_value = ft_strndup(&input[start], i - start);

		ft_create_add_token(shell, type, token_value);
		free(token_value);
	}
	
}

// Generate the tokens from the shell->user_input
int lexer(t_shell *shell)
{

	printf("User input: %s\n", shell->user_input);
	if (!shell->user_input)
	{
		printf("No user input received in lexer\n");
		return (EXIT_FAILURE);
	}
	else if (ft_strcmp(shell->user_input, "/0") == 0)
	{
		printf("There was an issue with the user input in lexer\n");
		return (EXIT_FAILURE);
	}

	ft_tokenize_input(shell->user_input, shell);
	ft_print_tokens(shell->token_list);
	add_history(shell->user_input);
	return (0);
}