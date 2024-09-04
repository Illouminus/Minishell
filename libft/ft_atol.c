/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:58:57 by edouard           #+#    #+#             */
/*   Updated: 2024/09/04 13:49:01 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

static bool	ft_is_number(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

static long	ft_handle_overflow(int sign)
{
	errno = ERANGE;
	if (sign == 1)
		return (LONG_MAX);
	return (LONG_MIN);
}

static long	ft_atol_core(const char *str)
{
	long	result;
	int		sign;
	long	prev_result;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		prev_result = result;
		result = result * 10 + (*str - '0');
		str++;
		if (result < prev_result)
			return (ft_handle_overflow(sign));
	}
	return (result * sign);
}

long	ft_atol(const char *str)
{
	if (!ft_is_number(str))
	{
		errno = ERANGE;
		return (0);
	}
	return (ft_atol_core(str));
}
