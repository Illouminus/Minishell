/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:31 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:01:32 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/* int	main(void)
{
	char test_chars[] = "aZ&";
	int i = 0;

	while (test_chars[i])
	{
		int original = isalpha(test_chars[i]);
		int custom = ft_isalpha(test_chars[i]);

		if (original != custom)
		{
			printf("Test failed for '%c': original %d, custom %d\n",
				test_chars[i], original, custom);
			return (1);
		}
		i++;
	}
	printf("All tests passed!\n");
	return (0);
} */