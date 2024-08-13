/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:38:33 by edouard           #+#    #+#             */
/*   Updated: 2024/08/12 15:37:47 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction d'affichage temporaire | A supprimer plus tard
void ft_print_tokens(t_token *token_list)
{
	t_token *current = token_list;
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
    int i = 0;
    int is_first_token = 1;

    while (input[i])
    {
        i = ft_skip_whitespace(input, i);
        if (input[i] == '\0')
            break;

        int start = i;
        if (input[i] == '"' || input[i] == '\'')
            i = ft_handle_quotes(input, i);
        else if (ft_is_special_char(input[i]))
            i++;  // Handle single special character as token
        else
            i = ft_parse_regular_token(input, i);

        t_token_type type = ft_determine_token_type(input, start, is_first_token);
        is_first_token = (type == TOKEN_TYPE_PIPE);

        char *token_value = ft_strndup(&input[start], i - start);
        ft_create_add_token(shell, type, token_value);
        free(token_value);
    }
}




// Generate the tokens from the shell->user_input
int lexer(t_shell *shell)
{

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
	// ft_print_tokens(shell->token_list);
	add_history(shell->user_input);
	return (0);
}