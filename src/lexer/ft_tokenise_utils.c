/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenise_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:48:52 by ahors             #+#    #+#             */
/*   Updated: 2024/08/12 15:36:59 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to ignore whitespaces
int ft_skip_whitespace(char *input, int i)
{
	while (ft_isspace(input[i]))
		i++;
	return i;
}

int ft_is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

int ft_parse_regular_token(char *input, int i)
{
    while (input[i] != '\0' && !ft_isspace(input[i]) && !ft_is_special_char(input[i]) && input[i] != '"' && input[i] != '\'')
        i++;
    return i;
}

int ft_handle_quotes(char *input, int i)
{
    char quote_char = input[i++];
    while (input[i] && input[i] != quote_char)
        i++;
    if (input[i] == quote_char)
        return i + 1; // Move past closing quote
    else
    {
        printf("Erreur: guillemet fermant manquant pour le caractère '%c'.\n", quote_char);
		// TODO - EXIT et free tout
        return -1; // Indique qu'une erreur est survenue
    }
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
