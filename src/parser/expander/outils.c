/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:39:36 by edouard           #+#    #+#             */
/*   Updated: 2024/08/30 11:28:57 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_char_to_result(char **result, int *j, char c)
{
	(*result)[(*j)++] = c;
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*extract_var_name(const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
