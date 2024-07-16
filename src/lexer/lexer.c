/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:38:33 by edouard           #+#    #+#             */
/*   Updated: 2024/07/16 14:13:26 by ahors            ###   ########.fr       */
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
	 
	if (shell->token_list == NULL) {
        shell->token_list = new_token;
    } else {
        temp = shell->token_list;
        while (temp->next_tok != NULL) {
            temp = temp->next_tok;
        }
        temp->next_tok = new_token;
        new_token->prev_tok = temp;
    }
}


void ft_tokenize_input(char *input, t_shell *shell) {
    char buffer[1024];
    int buf_index = 0;
    int quote_status = 0; // 0 = no quote, 1 = single quote, 2 = double quote
    int i = 0;

    while (input[i] != '\0') {
        char c = input[i];

        if (c == ' ' && quote_status == 0) {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                if (shell->token_list == NULL) {
                    ft_add_token(shell, ft_create_token(TOK_TYPE_CMD, buffer, quote_status));
                } else {
                    ft_add_token(shell, ft_create_token(TOK_TYPE_ARG, buffer, quote_status));
                }
                buf_index = 0;
            }
        } else if (c == '\'') {
            if (quote_status == 1) {
                quote_status = 0;
            } else if (quote_status == 0) {
                quote_status = 1;
            } else {
                buffer[buf_index++] = c;
            }
        } else if (c == '\"') {
            if (quote_status == 2) {
                quote_status = 0;
            } else if (quote_status == 0) {
                quote_status = 2;
            } else {
                buffer[buf_index++] = c;
            }
        } else if (c == '|' && quote_status == 0) {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                ft_add_token(shell, ft_create_token(TOK_TYPE_ARG, buffer, quote_status));
                buf_index = 0;
            }
            ft_add_token(shell, ft_create_token(TOK_TYPE_PIPE, "|", quote_status));
        } else if ((c == '>' || c == '<') && quote_status == 0) {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                ft_add_token(shell, ft_create_token(TOK_TYPE_ARG, buffer, quote_status));
                buf_index = 0;
            }
            char next_c = input[i + 1];
            if (next_c == c) {
                i++;
                char redir_op[3] = {c, c, '\0'};
                ft_add_token(shell, ft_create_token(TOK_TYPE_REDIR, redir_op, quote_status));
            } else {
                char redir_op[2] = {c, '\0'};
                ft_add_token(shell, ft_create_token(TOK_TYPE_REDIR, redir_op, quote_status));
            }
        } else {
            buffer[buf_index++] = c;
        }

        i++;
    }

    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        if (shell->token_list == NULL) {
            ft_add_token(shell, ft_create_token(TOK_TYPE_CMD, buffer, quote_status));
        } else {
            ft_add_token(shell, ft_create_token(TOK_TYPE_ARG, buffer, quote_status));
        }
    }
}


//Testing Tokens are good 
void ft_print_tokens(t_token *token_list) {
    t_token *current = token_list;
    while (current != NULL) {
        printf("Token: %s, Type: %d, Quote Status: %d\n", current->tok_value, current->tok_type, current->quote_status);
        current = current->next_tok;
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
	//Lines to free token_list between each command --> Mettre dans une fonction a part
	t_token *temp;
	while (shell->token_list != NULL) {
		temp = shell->token_list;
		shell->token_list = shell->token_list->next_tok;
		free(temp->tok_value);
		free(temp);
	}
	return 0;
}