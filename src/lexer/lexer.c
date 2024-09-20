/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:38:33 by edouard           #+#    #+#             */
/*   Updated: 2024/09/19 18:22:03 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool contains_heredoc(const char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			return (true);
		i++;
	}
	return (false);
}

// Fonction d'affichage temporaire | A supprimer plus tard
void ft_print_tokens(t_token *token_list)
{
	t_token *current;

	current = token_list;
	while (current != NULL)
	{
		printf("Token: %s, Type: %d\n", current->tok_value, current->tok_type);
		current = current->next_tok;
	}
	printf("\n\n");
}

void ft_process_token(char *input, t_token_context *context,
							 int *is_first_token, t_shell *shell)
{
	t_token_type type;
	char *token_value;

	type = ft_determine_token_type(input, context->start, *is_first_token);
	*is_first_token = (type == TOKEN_TYPE_PIPE);
	token_value = ft_strndup(&input[context->start], context->i - context->start);
	ft_create_add_token(shell, type, token_value);
	free(token_value);
}

void ft_tokenize_input(char *input, t_shell *shell)
{
	int i;
	int is_first_token;
	int inside_quote;
	t_token_context context;

	i = 0;
	is_first_token = 1;
	inside_quote = 0;
	while (input[i])
	{
		i = ft_skip_whitespace(input, i);
		if (input[i] == '\0')
			break;
		context.start = i;
		if (ft_is_special_char(input[i]) && !inside_quote)
			i++;
		else
		{
			i = ft_parse_regular_token(input, i, &inside_quote, shell);
			if (i == -1)
				return;
		}
		context.i = i;
		ft_process_token(input, &context, &is_first_token, shell);
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
	if (!contains_heredoc(shell->user_input))
		add_history(shell->user_input);
	ft_tokenize_input(shell->user_input, shell);
	return (0);
}
