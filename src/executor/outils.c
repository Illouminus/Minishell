/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:48:27 by edouard           #+#    #+#             */
/*   Updated: 2024/07/23 14:12:07 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(char *cmd, char *error_message)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

char *ft_getenv(t_env *env_list, const char *name)
{
	t_env *var = ft_get_env_var_by_name(env_list, name);
	if (var)
	{
		return strdup(var->env_value);
	}
	return NULL;
}

void ft_setenv(t_env **env_list, const char *name, const char *value)
{
	t_env *var = ft_get_env_var_by_name(*env_list, name);
	if (var)
	{
		free(var->env_value);
		var->env_value = strdup(value);
	}
	else
	{
		t_env *new_var = malloc(sizeof(t_env));
		if (new_var)
		{
			new_var->env_var_name = strdup(name);
			new_var->env_value = strdup(value);
			new_var->next_env = *env_list;
			*env_list = new_var;
		}
	}
}
