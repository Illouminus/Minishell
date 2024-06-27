/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:59:57 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:32:25 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;

	d = dest;
	if (s < d && s + n > d)
	{
		while (n--)
			d[n] = s[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/* int main(void) {
		char str[] = "memmove can be very useful......";
		ft_memmove(str + 20, str + 15, 11);
		printf("ft_memmove result: %s\n", str);

		char expected[] = "memmove can be very very useful......";
		if (strcmp(str, expected) != 0) {
			printf("Test failed: the result
			 of ft_memmove does not match expected output\n");
			return (1);
		}

		printf("ft_memmove test passed.\n");
		return (0);
} */