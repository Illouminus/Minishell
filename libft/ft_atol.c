/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:58:57 by edouard           #+#    #+#             */
/*   Updated: 2024/08/12 10:03:33 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

static bool ft_is_number(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			 *str == '\v' || *str == '\f' || *str == '\r')
		str++;

	if (*str == '-' || *str == '+')
		str++;

	while (*str)
	{
		if (*str < '0' || *str > '9')
			return false;
		str++;
	}

	return true;
}

static long ft_atol_core(const char *str)
{
	long result = 0;
	int sign = 1;

	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			 *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		long prev_result = result;
		result = result * 10 + (*str - '0');
		str++;
		if (result < prev_result)
		{
			errno = ERANGE;
			return (sign == 1 ? LONG_MAX : LONG_MIN);
		}
	}
	return result * sign;
}

long ft_atol(const char *str)
{
	if (!ft_is_number(str))
	{
		errno = ERANGE;
		return 0;
	}
	return ft_atol_core(str);
}
