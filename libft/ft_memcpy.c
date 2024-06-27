/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:40:24 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:03:52 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n != 0)
	{
		((unsigned char *)dst)[i] = ((char *)src)[i];
		i++;
		n--;
	}
	return (dst);
}

/* int main(void) {
		char src[] = "Test string";
		char dest[100];

		ft_memcpy(dest, src, strlen(src) + 1);

		if (strcmp(dest, src) != 0) {
			printf("Test failed: copied string does not match original\n");
			return (1);
		} else {
			printf("ft_memcpy test passed: %s\n", dest);
		}

		ft_memcpy(src + 5, src, 7);
		printf("ft_memcpy overlap test result: %s\n", src);

		return (0);
} */