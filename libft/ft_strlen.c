/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:11 by ebaillot          #+#    #+#             */
/*   Updated: 2024/09/04 13:44:10 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/* int main() {
		const char *str = "Hello, World!";
		size_t len = ft_strlen(str);
		size_t expected_len = strlen(str);

		printf("Length of '%s': %zu (expected: %zu)\n", str, len, expected_len);

		if (len != expected_len) {
			printf("Test failed: Length does not match the expected length.\n");
			return (1);
		}

		str = "";
		len = ft_strlen(str);
		expected_len = strlen(str);

		printf("Length of an empty string: %zu (expected: %zu)\n", len,
			expected_len);

		if (len != expected_len) {
			printf("Test failed: Length of an empty string is not zero.\n");
			return (1);
		}

		printf("All tests passed.\n");
		return (0);
} */