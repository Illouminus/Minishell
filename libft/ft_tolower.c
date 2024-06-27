/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:56:45 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:05:43 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/* int main() {
		for (int i = 0; i < 256; i++) {
			if (ft_tolower(i) != tolower(i)) {
				printf("Test failed for %c: ft_tolower %d, tolower %d\n", i,
					ft_tolower(i), tolower(i));
				return (1);
			}
		}
		printf("All tests passed for ft_tolower.\n");
		return (0);
} */