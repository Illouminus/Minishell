/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:45:45 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:05:33 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	a;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		a = 0;
		while (haystack[i + a] == needle[a] && i + a < len)
		{
			if (needle[a + 1] == '\0')
				return ((char *)&haystack[i]);
			a++;
		}
		i++;
	}
	return (NULL);
}

/* int main(void)
{
	const char *haystack = "Hello World!";
	const char *needle = "World";
	size_t len = 10;


	char *result = ft_strnstr(haystack, needle, len);
	char *expected = strnstr(haystack, needle, len);
	printf("Test 1 - Expected: %s, Result: %s\n", expected, result);


	len = 5;
	result = ft_strnstr(haystack, needle, len);
	expected = strnstr(haystack, needle, len);
	printf("Test 2 - Expected: %p, Result: %p\n", (void *)expected,
		(void *)result);


	needle = "";
	result = ft_strnstr(haystack, needle, len);
	expected = strnstr(haystack, needle, len);
	printf("Test 3 - Expected: %s, Result: %s\n", expected, result);


	haystack = "Short";
	len = 10;
	result = ft_strnstr(haystack, needle, len);
	expected = strnstr(haystack, needle, len);
	printf("Test 4 - Expected: %s, Result: %s\n", expected, result);


	needle = "Hello";
	result = ft_strnstr(haystack, needle, len);
	expected = strnstr(haystack, needle, len);
	printf("Test 5 - Expected: %s, Result: %s\n", expected, result);


	needle = "nonexistent";
	result = ft_strnstr(haystack, needle, len);
	expected = strnstr(haystack, needle, len);
	printf("Test 6 - Expected: %p, Result: %p\n", (void *)expected,
		(void *)result);

	return (0);
} */