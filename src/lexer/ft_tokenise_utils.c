/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenise_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:48:52 by ahors             #+#    #+#             */
/*   Updated: 2024/07/16 16:15:50 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Create a single token
t_token *ft_create_token(int type, char *value, int quote_status) 
{
    t_token *new_token;
	
	new_token = (t_token *)malloc(sizeof(t_token));
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


// Fonction pour traiter les guillemets dans le shell->user_input
int ft_process_quotes(char c, int quote_status)
{
    if (c == '\'') 
    {
        if (quote_status == 1)
            return 0;  // Fermeture des guillemets simples
        else if (quote_status == 0) 
            return 1;  // Ouverture des guillemets simples
    } 
    else if (c == '\"') 
    {
        if (quote_status == 2)
            return 0;  // Fermeture des guillemets doubles
        else if (quote_status == 0) 
            return 2;  // Ouverture des guillemets doubles
    }
    return quote_status;  // Aucun changement de statut de guillemets
}

// Fonction pour traiter les opérateurs de redirection dans le shell->user_input
void ft_process_redirection(char c, char next_c, t_shell *shell, char *buffer, int *buf_index, int quote_status, int *i) 
{
    if ((c == '>' || c == '<') && quote_status == 0) 
    {
        if (*buf_index > 0) 
        {
            buffer[*buf_index] = '\0';
            ft_create_add_argument_token(shell, buffer, quote_status);
            *buf_index = 0;
        }
        if (next_c == c) 
        {
            (*i)++;
            char redir_op[3] = {c, c, '\0'};
            ft_create_add_redirection_token(shell, redir_op, quote_status);
        } else 
        {
            char redir_op[2] = {c, '\0'};
           ft_create_add_redirection_token(shell, redir_op, quote_status);
        }
    }
}

// Fonction pour traiter les espaces et construire les tokens
void ft_process_spaces(char c, t_shell *shell, char *buffer, int *buf_index, int quote_status) 
{
    if (c == ' ' && quote_status == 0) 
    {
        if (*buf_index > 0) {
            buffer[*buf_index] = '\0';
            if (shell->token_list == NULL) 
                ft_create_add_command_token(shell, buffer, quote_status);
            else 
                ft_create_add_argument_token(shell, buffer, quote_status);
            *buf_index = 0;
        }
    }
}