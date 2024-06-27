/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:03:03 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:05:30 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	if (n == 0)
		return (0);
	while (s1[a] == s2[a] && s1[a] != '\0' && a < n - 1)
		a++;
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}

/* int main() {
		char str1[] = "hello";
		char str2[] = "hello world";
		char str3[] = "hellO";

		printf("ft_strncmp: %d\n", ft_strncmp(str1, str2, 5));

		printf("ft_strncmp: %d\n", ft_strncmp(str1, str2, 10));

		printf("ft_strncmp: %d\n", ft_strncmp(str1, str3, 5));

		return (0);
} */