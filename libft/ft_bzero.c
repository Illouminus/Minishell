/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:24:44 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:01:24 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

/* int main() {
		char test[10];

		ft_memset(test, 'a', 10);
		ft_bzero(test, 5);


		for (int i = 0; i < 10; i++) {
			if (i < 5 && test[i] != '\0') {
				printf("Test failed at index %d: byte is not zero\n", i);
				return (1);
			}
			if (i >= 5 && test[i] != 'a') {
				printf("Test failed at index %d: byte is not 'a'\n", i);
				return (1);
			}
		}

		printf("ft_bzero test passed!\n");
		return (0);
} */