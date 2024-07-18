/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:38:33 by edouard           #+#    #+#             */
/*   Updated: 2024/07/18 13:38:59 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction d'affichage temporaire | A supprimer plus tard
void ft_print_tokens(t_token *token_list)
{
    t_token *current = token_list;
    while (current != NULL) 
    {
        printf("Token: %s, Type: %d\n", current->tok_value, current->tok_type);
        current = current->next_tok;
    }
}

// Fonction principale de tokenisation
void ft_tokenize_input(char *input, t_shell *shell) {
    int i = 0;
    int start = 0;
    char quote_char = '\0';
    t_token_type type;
    int is_first_token = 1;

    while (input[i] != '\0') {
        // Skip whitespace
        i = ft_skip_whitespace(input, i);
        
        if (input[i] == '\0') {
            break;
        }

        start = i;

        // Handle quotes
        if (input[i] == '"' || input[i] == '\'') {
            i = ft_handle_quotes(input, i, &quote_char);
            if (i == -1) {
                return; // Unmatched quote error
            }
        } else {
            while (input[i] != '\0' && !ft_isspace(input[i]) && input[i] != '"' && input[i] != '\'') {
                i++;
            }
        }

        // Determine the type of the token
        type = ft_determine_token_type(input, start, is_first_token); 
        if (type ==  TOKEN_TYPE_PIPE)
            is_first_token = 1;
        else   
            is_first_token = 0;

        // Create and add the token
        char *token_value = strndup(&input[start], i - start);
        t_token *new_token = ft_create_token(type, token_value);
        ft_add_token(shell, new_token);
        free(token_value);
    }

    // Add end-of-file token
    t_token *eof_token = ft_create_token(TOKEN_TYPE_EOF, "EOF");
    ft_add_token(shell, eof_token);
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
	//Lines to free token_list between each command --> Put in a separate function
	t_token *temp;
	while (shell->token_list != NULL) {
		temp = shell->token_list;
		shell->token_list = shell->token_list->next_tok;
		free(temp->tok_value);
		free(temp);
	}
	return (0);
}