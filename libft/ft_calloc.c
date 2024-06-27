/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:01:48 by ebaillot          #+#    #+#             */
/*   Updated: 2023/12/21 14:05:16 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*loc;

	if (nmemb == 0 || size == 0)
	{
		size = 1;
		nmemb = size;
	}
	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	loc = malloc(nmemb * size);
	if (!loc)
		return (NULL);
	ft_bzero(loc, nmemb * size);
	return (loc);
}

/* int main()
{
	size_t count, size;
	int *array;

	count = 10;
	size = sizeof(int);
	array = (int *)ft_calloc(count, size);
	if (array == NULL)
	{
		printf("Test 1 failed: memory allocation failed\n");
	}
	else
	{
		for (size_t i = 0; i < count; i++)
		{
			if (array[i] != 0)
			{
				printf("Test 1 failed: memory not set to zero at index %zu\n",
					i);
				free(array);
				return (1);
			}
		}
		printf("Test 1 passed\n");
		free(array);
	}

	count = 0;
	size = sizeof(int);
	array = (int *)ft_calloc(count, size);
	if (array != NULL)
	{
		printf("Test 2 failed: memory should not be allocated\n");
		free(array);
	}
	else
	{
		printf("Test 2 passed\n");
	}

	return (0);
} */