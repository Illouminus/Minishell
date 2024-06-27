/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:41:24 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 13:32:11 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;

	if (n == 0)
		return (0);
	while (n--)
	{
		if (*p1 != *p2)
		{
			return (*p1 - *p2);
		}
		p1++;
		p2++;
	}
	return (0);
}

/* int main() {
		char str1[] = "abcdef";
		char str2[] = "abcDef";
		char str3[] = "abcdef";


		int result = ft_memcmp(str1, str2, 6);
		if (result == 0) {
			printf("Error: strings are different but 
			ft_memcmp did not return (non-zero\n"));
		} else {
			printf("Correct: ft_memcmp returned %d for different strings\n",
				result);
		}


		result = ft_memcmp(str1, str3, 6);
		if (result != 0) {
			printf("Error: strings are the same but
			 ft_memcmp returned non-zero\n");
		} else {
			printf("Correct: ft_memcmp returned %d for identical strings\n",
				result);
		}


		result = ft_memcmp(str1, str1, 6);
		if (result != 0) {
			printf("Error: ft_memcmp comparing string
			 to itself did not return (zero\n"));
		} else {
			printf("Correct: ft_memcmp comparing string to itself returned
				%d\n", result);
		}

		return (0);
} */