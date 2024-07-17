/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:38:33 by edouard           #+#    #+#             */
/*   Updated: 2024/07/17 15:18:00 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_print_tokens(t_token *token_list)
{
    t_token *current = token_list;
    while (current != NULL) 
    {
        printf("Token: %s, Type: %d, Quote Status: %d\n", current->tok_value, current->tok_type, current->quote_status);
        current = current->next_tok;
    }
}

void ft_tokenize_input(char *input, t_shell *shell)
{
    t_token *tokens = NULL;
    char buffer[256];
    int buffer_index = 0;
    int length = ft_strlen(shell->user_input);
    int i = 0;

    while (i <= length)
    {
        i++;
         if (isspace(input[i]) || input[i] == '\0') {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                t_token type = ft_determine_token_type(buffer);
                t_token *new_token = create_token(type, buffer);
                append_token(&tokens, new_token);
                buffer_index = 0;
            }
        } else if (input[i] == '|' || input[i] == '<' || input[i] == '>' || input[i] == '&') {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                t_token type = ft_determine_token_type(buffer);
                Token *new_token = create_token(type, buffer);
                append_token(&tokens, new_token);
                buffer_index = 0;
            }
            buffer[0] = input[i];
            buffer[1] = '\0';
            t_token type = ft_determine_token_type(buffer);
            Token *new_token = create_token(type, buffer);
            append_token(&tokens, new_token);
        } else {
            buffer[buffer_index++] = input[i];
        }
    }
    
    return tokens;    
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