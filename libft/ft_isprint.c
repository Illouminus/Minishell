/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:32:08 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:02:34 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/* int main(void) {
		for (int i = 0; i < 256; i++) {
			if (ft_isprint(i) != isprint(i)) {
				printf("Test failed for %d: ft_isprint %d, isprint %d\n", i,
					ft_isprint(i), isprint(i));
				return (1);
			}
		}
		printf("All tests passed for ft_isprint.\n");
		return (0);
} */