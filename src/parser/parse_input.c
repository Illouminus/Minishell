/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/07/02 09:02:26 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int count_words(char *str)
{
	int count = 0;
	int in_word = 0;

	while (*str)
	{
		if (!is_whitespace(*str) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_whitespace(*str))
		{
			in_word = 0;
		}
		str++;
	}
	return count;
}

char **parse_input(char *input)
{
	int i = 0;
	int word_count = count_words(input);
	char **args = malloc((word_count + 1) * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (*input)
	{
		while (is_whitespace(*input))
			input++;
		if (*input)
		{
			char *start = input;
			while (*input && !is_whitespace(*input))
				input++;
			int len = input - start;
			args[i] = malloc(len + 1);
			if (!args[i])
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			strncpy(args[i], start, len);
			args[i][len] = '\0';
			i++;
		}
	}
	args[i] = NULL;
	return args;
}