/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:29:52 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:02:29 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/* int main(void) {
		for (int i = 0; i < 256; i++) {
			if (ft_isascii(i) != isascii(i)) {
				printf("Test failed for %d: ft_isascii %d, isascii %d\n", i,
					ft_isascii(i), isascii(i));
				return (1);
			}
		}
		printf("All tests passed for ft_isascii.\n");
		return (0);
} */