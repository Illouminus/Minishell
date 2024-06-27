/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:24:04 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:05:28 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* char my_func(unsigned int i, char c)
{
	(void)i;
	return (ft_toupper(c));
}

int	main(void)
{
	char const *s = "hello world";
	char *result = ft_strmapi(s, my_func);

	if (result == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}

	printf("Original string: %s\n", s);
	printf("Transformed string: %s\n", result);

	free(result);
	return (0);
} */