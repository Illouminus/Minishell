/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:26 by edouard           #+#    #+#             */
/*   Updated: 2024/08/06 17:19:48 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unsetenv(t_env **env_list, const char *name)
{
	t_env *current = *env_list;
	t_env *previous = NULL;

	while (current)
	{
		if (ft_strcmp(current->env_var_name, name) == 0)
		{
			if (previous)
				previous->next_env = current->next_env;
			else
				*env_list = current->next_env;
			free(current->env_var_name);
			free(current->env_value);
			free(current);
			return;
		}
		previous = current;
		current = current->next_env;
	}
}

int ft_builtin_unset(t_command *cmd, t_env **env_list)
{
	int i;

	i = 0;

	if (!cmd->cmd_args[1])
	{
		print_error("unset", "not enough arguments");
		return 1;
	}

	while (cmd->cmd_args[i])
	{

		ft_unsetenv(env_list, cmd->cmd_args[i]);
		i++;
	}

	return 0;
}