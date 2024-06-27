/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:13:23 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:35:09 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*entry;

	entry = NULL;
	if (c == '\0')
	{
		return ((char *)(s + ft_strlen(s)));
	}
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			entry = s;
		}
		s++;
	}
	return ((char *)entry);
}

/* int main() {
		const char str[] = "Find the last character 't' in this string! ttt";
		int ch = 't';
		char *result = ft_strrchr(str, ch);

		if (result != NULL) {
			printf("Last occurrence of character '%c' found at position: %ld\n",
				ch, result - str);
		} else {
			printf("Character '%c' not found.\n", ch);
		}

		result = ft_strrchr(str, '\0');
		if (result != NULL && *result == '\0') {
			printf("The null terminator was found at the end of the string.\n");
		} else {
			printf("The null terminator was not found.\n");
		}

		result = ft_strrchr(str, 'z');
		if (result != NULL) {
			printf("Error: character 'z' was found.\n");
		} else {
			printf("Character 'z' was not found, which is correct.\n");
		}

		return (0);
} */