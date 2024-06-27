/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:26:51 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:02:31 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)

{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/* int main(void) {
		for (int i = 0; i < 256; i++) {
			if (ft_isdigit(i) != isdigit(i)) {
				printf("Test failed for %d: ft_isdigit %d, isdigit %d\n", i,
					ft_isdigit(i), isdigit(i));
				return (1);
			}
		}
		printf("All tests passed for ft_isdigit.\n");
		return (0);
} */
