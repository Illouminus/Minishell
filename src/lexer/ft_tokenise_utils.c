/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenise_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:48:52 by ahors             #+#    #+#             */
/*   Updated: 2024/08/07 10:57:53 by edouard          ###   ########.fr       */
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

// Function to hanles quotes
int ft_handle_quotes(char *input, int i, char *quote_char)
{
	*quote_char = input[i];
	i++;
	while (input[i] != '\0' && input[i] != *quote_char)
		i++;
	if (input[i] == *quote_char)
		i++; // Move past the closing quote
	else
	{
		// Handle error for unmatched quotes
		printf("Error: Unmatched quote\n");
		return -1;
	}
	return i;
}
