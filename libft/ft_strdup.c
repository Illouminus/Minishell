/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:00:33 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:05:08 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*loc;
	size_t	i;

	loc = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!loc)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		loc[i] = s1[i];
		i++;
	}
	loc[i] = 0;
	return (loc);
}

/* int main()
{
	const char *original = "Test string";
	char *duplicate;

	duplicate = ft_strdup(original);
	if (duplicate == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}

	if (strcmp(original, duplicate) != 0)
	{
		printf("Strings are not the same\n");
		free(duplicate);
		return (1);
	}
	else
	{
		printf("ft_strdup works correctly\n");
	}

	free(duplicate);

	original = "";
	duplicate = ft_strdup(original);
	if (duplicate == NULL)
	{
		printf("Memory allocation failed for empty string\n");
		return (1);
	}

	if (strcmp(original, duplicate) != 0)
	{
		printf("Empty string duplication failed\n");
		free(duplicate);
		return (1);
	}
	else
	{
		printf("ft_strdup correctly duplicates an empty string\n");
	}

	free(duplicate);
	return (0);
} */