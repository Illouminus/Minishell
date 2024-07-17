/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenise_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:48:52 by ahors             #+#    #+#             */
/*   Updated: 2024/07/17 15:11:48 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Create a single token
t_token *ft_create_token(int type, char *value, int quote_status) 
{
    t_token *new_token;
	
	new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
        return(NULL);
    new_token->tok_type = type;
    new_token->tok_value = ft_strdup(value);
    new_token->quote_status = quote_status;
    new_token->next_tok = NULL;
    new_token->prev_tok = NULL;
    return (new_token);
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

// Fonction pour déterminer le type d'un token
t_token_type ft_determine_token_type(const char *str) 
{
    if (strcmp(str, "|") == 0) return TOKEN_TYPE_PIPE;
    if (strcmp(str, "<") == 0) return TOKEN_TYPE_REDIR_IN;
    if (strcmp(str, ">") == 0) return TOKEN_TYPE_REDIR_IN;
    if (str[0] == '-') return TOKEN_TYPE_ARG;
    return TOKEN_TYPE_CMD;
}