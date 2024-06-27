/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:46:52 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:32:46 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (n != 0)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
		n--;
	}
	return (s);
}

/* int main(void) {
		char str[50] = 
		"GeeksForGeeks is for programming geeks.";

		printf("\nBefore ft_memset(): %s\n", str);
		ft_memset(str + 13, '.', 8);
		printf("After ft_memset():  %s\n", str);

		char expected[50] = "GeeksForGeeks .......
		.programming geeks.";
		if (strcmp(str, expected) != 0) {
			printf("Test failed: the result of
			 ft_memset does not match expected output\n");
			return (1);
		}

		printf("ft_memset test passed.\n");
		return (0);
} */