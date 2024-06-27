/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:41:46 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:05:45 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

/* int main() {
		for (int i = 0; i < 256; i++) {
			if (ft_toupper(i) != toupper(i)) {
				printf("Test failed for %c: ft_toupper %d, toupper %d\n", i,
					ft_toupper(i), toupper(i));
				return (1);
			}
		}
		printf("All tests passed for ft_toupper.\n");
		return (0);
} */