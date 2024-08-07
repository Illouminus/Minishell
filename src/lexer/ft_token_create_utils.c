/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:50:44 by ahors             #+#    #+#             */
/*   Updated: 2024/08/07 12:28:32 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//Create a single token
t_token *ft_create_token(int type, char *value)
{
    t_token *new_token;
	
	new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
    {
		printf("Error in tokens creation, during create_token\n");
        return(NULL);
    }
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

    if (input[start] == '|')
    {
        type = TOKEN_TYPE_PIPE;
    } else if (input[start] == '<') 
    {
        type = TOKEN_TYPE_REDIR_IN;
    } else if (input[start] == '>') 
    {
        type = TOKEN_TYPE_REDIR_OUT;
    } else if (is_first_token) 
    {
        type = TOKEN_TYPE_CMD;
    } else 
    {
        type = TOKEN_TYPE_ARG;
    }
    return type;
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
        while (temp->next_tok != NULL)
            temp = temp->next_tok;
        temp->next_tok = new_token;
        new_token->prev_tok = temp;
    }
}

// Fonction pour creer et ajouter un token de type commande
void ft_create_add_token(t_shell *shell, int type, char *value)
{
    ft_add_token(shell, ft_create_token(type, value));
}
