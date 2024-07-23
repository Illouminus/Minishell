/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:17 by edouard           #+#    #+#             */
/*   Updated: 2024/07/23 11:11:54 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_builtin_env(t_env *env)
{
	t_env *current;

	current = env;

	while (current)
	{
		if (current->env_var_name)
		{
			ft_putstr_fd(current->env_var_name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->env_value, 1);
			ft_putstr_fd("\n", 1);
		}
		current = current->next_env;
	}
	return (EXIT_SUCCESS);
}