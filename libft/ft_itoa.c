/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:11:48 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:24:32 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, long nbr, int len)
{
	while (nbr > 0)
	{
		str[--len] = '0' + (nbr % 10);
		nbr /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nbr;

	nbr = n;
	len = get_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	else
	{
		if (n < 0)
		{
			str[0] = '-';
			nbr = -nbr;
		}
		fill_str(str, nbr, len);
	}
	return (str);
}

/* int main()
{
	int test_values[] = {0, 1, -1, 1234, -1234, INT_MAX, INT_MIN};
	int num_tests = sizeof(test_values) / sizeof(test_values[0]);
	char *result;

	for (int i = 0; i < num_tests; ++i)
	{
		result = ft_itoa(test_values[i]);
		if (result != NULL)
		{
			printf("ft_itoa(%d) = %s\n", test_values[i], result);
			free(result);
		}
		else
		{
			printf("ft_itoa(%d) failed to allocate memory.\n", test_values[i]);
		}
	}

	return (0);
} */