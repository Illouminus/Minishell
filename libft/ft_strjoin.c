/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:07:46 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:05:18 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len_s1 + 1);
	i = 0;
	while (s2[i] != '\0')
	{
		str[len_s1 + i] = s2[i];
		i++;
	}
	str[len_s1 + i] = '\0';
	return (str);
}

/* int main()
{
	const char *str1 = "Hello, ";
	const char *str2 = "World!";
	char *joined_str = ft_strjoin(str1, str2);

	if (joined_str == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}

	printf("Joined string: %s\n", joined_str);

	if (strcmp(joined_str, "Hello, World!") != 0)
	{
		printf("Test failed: the strings were not joined correctly.\n");
		free(joined_str);
		return (1);
	}

	free(joined_str);

	joined_str = ft_strjoin("", "");
	if (strcmp(joined_str, "") != 0)
	{
		printf("Test failed: empty strings were not joined correctly.\n");
		free(joined_str);
		return (1);
	}

	printf("Empty string test passed.\n");
	free(joined_str);

	return (0);
} */