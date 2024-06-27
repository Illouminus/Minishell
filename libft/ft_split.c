/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:10:06 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 14:00:29 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_separateur(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

int	count_words(const char *str, char sep)
{
	int	i;
	int	acc;

	i = 0;
	acc = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_separateur(str[i], sep))
			i++;
		if (str[i] != '\0')
			acc++;
		while (str[i] != '\0' && !is_separateur(str[i], sep))
			i++;
	}
	return (acc);
}

char	*allocate_word(const char *str, char sep)
{
	int		word_length;
	int		i;
	char	*word;

	word_length = 0;
	i = 0;
	while (str[word_length] != '\0' && !is_separateur(str[word_length], sep))
		word_length++;
	word = malloc(sizeof(char) * (word_length + 1));
	if (!word)
		return (NULL);
	while (i < word_length)
	{
		word[i] = str[i];
		i++;
	}
	word[word_length] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		global_length;
	int		i;
	char	**res;

	i = 0;
	if (!s)
		return (NULL);
	global_length = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (global_length + 1));
	if (!res)
		return (NULL);
	while (i < global_length)
	{
		while (*s && is_separateur(*s, c))
			s++;
		res[i] = allocate_word(s, c);
		if (!res[i++])
		{
			free_split(res);
			return (NULL);
		}
		while (*s && !is_separateur(*s, c))
			s++;
	}
	return (res[i] = NULL, res);
}

/* int main(void)
{
	const char string[] = "hello world how are you today";
	char c = ' ';
	char **words = ft_split(string, c);

	if (words == NULL)
		return (1);

	for (int i = 0; words[i] != NULL; i++)
	{
		printf("Word %d: %s\n", i, words[i]);
		free(words[i]);
	}
	free(words);

	return (0);
} */