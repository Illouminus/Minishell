/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:00:22 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:04:14 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/* int main() {
		const char str[] = "Find the character 't' in this string!";
		int ch = 't';
		char *result = ft_strchr(str, ch);

		if (result != NULL) {
			printf("Character '%c' found at position: %ld\n", ch, result - str);
		} else {
			printf("Character '%c' not found.\n", ch);
		}

		result = ft_strchr(str, '\0');
		if (result != NULL && *result == '\0') {
			printf("The null terminator was found at the end of the string.\n");
		} else {
			printf("The null terminator was not found.\n");
		}


		result = ft_strchr(str, 'z');
		if (result != NULL) {
			printf("Error: character 'z' was found.\n");
		} else {
			printf("Character 'z' was not found, which is correct.\n");
		}

		return (0);
} */