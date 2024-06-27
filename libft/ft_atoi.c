/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:40:19 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:01:20 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	accumulateur;
	int	i;
	int	sign;

	sign = 1;
	accumulateur = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		accumulateur = accumulateur * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * accumulateur);
}

/* int main(void)
{
	const char *test_strings[] = {
			"42",
			"   42",
			"-42",
			"+42",
			"0042",
			"-2147483648",
			"2147483647",
			"",
			"-2147483649",
			"2147483648",
			"invalid123",
			"123abc456",
			"   -42abc",
			"-+42",
			"----42",
			"  00000000000123456789",
			NULL
	};

	for (int i = 0; test_strings[i] != NULL; i++)
	{
		int val_atoi = atoi(test_strings[i]);
		int val_ft_atoi = ft_atoi(test_strings[i]);
		printf("Original atoi: %d, ft_atoi: %d, test case: '%s'\n",
					val_atoi, val_ft_atoi, test_strings[i]);
	}

	return (0);
} */