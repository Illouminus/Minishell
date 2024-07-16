/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:38:33 by edouard           #+#    #+#             */
/*   Updated: 2024/07/16 16:16:31 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// Fonction pour tokenizer l'entrée utilisateur
void ft_tokenize_input(char *input, t_shell *shell) 
{
    char buffer[1024];
    int buf_index = 0;
    int quote_status = 0; // 0 = no quote, 1 = single quote, 2 = double quote
    int i = 0;

    while (input[i] != '\0') {
        char c = input[i];
        char next_c = input[i + 1];

        quote_status = ft_process_quotes(c, quote_status);
        ft_process_redirection(c, next_c, shell, buffer, &buf_index, quote_status, &i);
        ft_process_spaces(c, shell, buffer, &buf_index, quote_status);

        if (quote_status == 0 && c == '|') {
            ft_create_add_pipe_token(shell);
        } else {
            buffer[buf_index++] = c;
        }

        i++;
    }

    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        if (shell->token_list == NULL) {
            ft_create_add_command_token(shell, buffer, quote_status);
        } else {
            ft_create_add_argument_token(shell, buffer, quote_status);
        }
    }
}

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