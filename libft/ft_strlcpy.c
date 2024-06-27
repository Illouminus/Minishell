/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:02:53 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:39:04 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (ft_strlen(src))
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
	}	
	if (dstsize > 0)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

/* int main() {
		const char src[] = "Copy this string!";
		char dest[19];

		size_t result = ft_strlcpy(dest, src, sizeof(dest));

		printf("ft_strlcpy result: %zu\n", result);
		printf("dest after strlcpy: '%s'\n", dest);


		size_t expected_len = strlen(src);
		if (result != expected_len) {
			printf("Test failed: the returned length is incorrect. Expected:
				%zu, Got: %zu\n", expected_len, result);
			return (1);
		}


		if (strcmp(dest, src) != 0) {
			printf("Test failed: the strings are not the same after copying.\n");
			return (1);
		}

		printf("Test passed.\n");
		return (0);
} */