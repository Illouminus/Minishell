/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:17:13 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:03:02 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p = (const unsigned char *)s;

	while (n-- > 0)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}

/* int main() {
		const char str[] = "example.com";
		int ch = 'e';
		char *ret;

		ret = ft_memchr(str, ch, strlen(str));
		if (ret != NULL) {
			printf("'%c' found in \"%s\" at position: %ld\n", ch, str, ret
				- str);
		} else {
			printf("'%c' not found in \"%s\"\n", ch, str);
		}

		ret = ft_memchr(str, 'z', strlen(str));
		if (ret != NULL) {
			printf("Error: 'z' found in \"%s\"\n", str);
		} else {
			printf("'z' not found in \"%s\", which is correct\n", str);
		}


		ch = '.';
		ret = ft_memchr(str, ch, 5);
		if (ret != NULL) {
			printf("Error: '%c' found in first 5 chars of \"%s\"\n", ch, str);
		} else {
			printf("'%c' not found in the first 5 chars of \"%s\",
				which is correct\n", ch, str);
		}

		return (0);
} */