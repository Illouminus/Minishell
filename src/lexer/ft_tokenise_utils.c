/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenise_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:48:52 by ahors             #+#    #+#             */
/*   Updated: 2024/09/16 13:18:33 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to ignore whitespaces
int	ft_skip_whitespace(char *input, int i)
{
	while (ft_isspace(input[i]))
		i++;
	return (i);
}

int	ft_is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_handle_quotes(t_shell *shell, char *input, int i, int *inside_quote)
{
	char	quote_char;

	quote_char = input[i++];
	*inside_quote = 1;
	while (input[i] && input[i] != quote_char)
		i++;
	if (input[i] == quote_char)
	{
		*inside_quote = 0;
		return (i + 1);
	}
	else
	{
		printf("Erreur: guillemet fermant manquant pour le caractère '%c'.\n",
			quote_char);
		free_shell(shell);
		return (-1);
	}
}

int	ft_parse_regular_token(char *input, int i, int *inside_quote,
		t_shell *shell)
{
	while (input[i] != '\0' && !ft_isspace(input[i])
		&& !ft_is_special_char(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i = ft_handle_quotes(shell, input, i, inside_quote);
			if (i == -1)
				return (-1);
		}
		else
			i++;
	}
	return (i);
}

// Determine the type of token
t_token_type	ft_determine_token_type(char *input, int start,
		int is_first_token)
{
	t_token_type	type;

	if (input[start] == '|')
		type = TOKEN_TYPE_PIPE;
	else if (input[start] == '<' && input[start + 1] == '<')
	{
		type = TOKEN_TYPE_HEREDOC;
		start += 2;
	}
	else if (input[start] == '<')
		type = TOKEN_TYPE_REDIR_IN;
	else if (input[start] == '>' && input[start + 1] == '>')
	{
		type = TOKEN_TYPE_REDIR_APPEND;
		start += 2;
	}
	else if (input[start] == '>')
		type = TOKEN_TYPE_REDIR_OUT;
	else if (is_first_token)
		type = TOKEN_TYPE_CMD;
	else
		type = TOKEN_TYPE_ARG;
	return (type);
}
