/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:43:03 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:05:39 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	index_start;
	size_t	index_end;

	if (!s1 || !set)
		return (NULL);
	index_start = 0;
	while (s1[index_start] && ft_strchr(set, s1[index_start]))
		index_start++;
	index_end = ft_strlen(s1);
	while (index_end > index_start && ft_strchr(set, s1[index_end - 1]))
		index_end--;
	str = malloc(sizeof(char) * (index_end - index_start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[index_start], index_end - index_start + 1);
	return (str);
}

/* int main()
{
	const char str1[] = "123hello world123";
	const char set1[] = "123";
	char *trimmed = ft_strtrim(str1, set1);

	if (trimmed == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}

	printf("Trimmed string (1): %s\n", trimmed);
	if (strcmp(trimmed, "hello world") != 0)
	{
		printf("Test failed: the strings were not trimmed correctly.\n");
		free(trimmed);
		return (1);
	}

	free(trimmed);

	const char str2[] = "hello world";
	const char set2[] = "123";
	trimmed = ft_strtrim(str2, set2);
	printf("Trimmed string (2): %s\n", trimmed);
	if (strcmp(trimmed, "hello world") != 0)
	{
		printf("Test failed: no trimming was needed but the string was changed.\n");
		free(trimmed);
		return (1);
	}

	free(trimmed);

	return (0);
} */