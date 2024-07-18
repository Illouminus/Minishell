/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenise_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:48:52 by ahors             #+#    #+#             */
/*   Updated: 2024/07/18 13:38:17 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Create a single token
t_token *ft_create_token(int type, char *value)
{
    t_token *new_token;
	
	new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
        return(NULL);
    new_token->tok_type = type;
    new_token->tok_value = ft_strdup(value);
    new_token->next_tok = NULL;
    new_token->prev_tok = NULL;
    return (new_token);
}

//Determine the type of token
t_token_type ft_determine_token_type(char *input, int start, int is_first_token)
{
    t_token_type type;

    if (input[start] == '|') {
        type = TOKEN_TYPE_PIPE;
    } else if (input[start] == '<') {
        type = TOKEN_TYPE_REDIR_IN;
    } else if (input[start] == '>') {
        type = TOKEN_TYPE_REDIR_OUT;
    } else if (is_first_token) {
        type = TOKEN_TYPE_CMD;
    } else {
        type = TOKEN_TYPE_ARG;
    }
    return type;
}


// Function to ignore whitespaces
int ft_skip_whitespace(char *input, int i)
{
    while (ft_isspace(input[i])) 
        i++;
    return i;
}

// Function to hanles quotes
int ft_handle_quotes(char *input, int i, char *quote_char) 
{
    *quote_char = input[i];
    i++;
    while (input[i] != '\0' && input[i] != *quote_char) 
    {
        i++;
    }
    if (input[i] == *quote_char) 
        i++; // Move past the closing quote
    else {
        // Handle error for unmatched quotes
        printf("Error: Unmatched quote\n");
        return -1;
    }
    return i;
}

//Add token to shell->tokens_list
void ft_add_token(t_shell *shell, t_token *new_token)
{
	t_token *temp;
	 
	if (shell->token_list == NULL) 
        shell->token_list = new_token;
    else 
    {
        temp = shell->token_list;
        while (temp->next_tok != NULL) {
            temp = temp->next_tok;
        }
        temp->next_tok = new_token;
        new_token->prev_tok = temp;
    }
}

