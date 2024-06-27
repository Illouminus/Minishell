/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:20:05 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 12:42:49 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_len;
	size_t	str_len;

	str_len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (str_len);
	dest_len = ft_strlen(dst);
	if (dstsize <= dest_len)
		return (str_len + dstsize);
	while (src[i] && (dest_len + i) < (dstsize - 1))
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[dest_len + i] = '\0';
	return (dest_len + str_len);
}

/* int main() {
		char dest[40] = "Hello";
		const char *src = " World";
		size_t dstsize = 40;

		size_t result = ft_strlcat(dest, src, dstsize);

		printf("ft_strlcat result: %zu\n", result);
		printf("dest after strlcat: '%s'\n", dest);


		size_t expected_len = strlen("Hello") + strlen(src);
		if (result != expected_len) {
			printf("Test failed: the returned length is incorrect.\n");
			return (1);
		}

		if (strcmp(dest, "Hello World") != 0) {
			printf("Test failed: the strings were not concatenated correctly.\n");
			return (1);
		}

		printf("Test passed.\n");
		return (0);
} */