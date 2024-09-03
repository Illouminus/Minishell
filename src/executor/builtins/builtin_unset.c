/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:26 by edouard           #+#    #+#             */
/*   Updated: 2024/09/03 16:22:52 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(t_env **env_list, const char *name)
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
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
			return ;
		}
		previous = current;
		current = current->next_env;
	}
}

int	ft_builtin_unset(t_command *cmd, t_env **env_list)
{
	int	i;

	i = 0;
	if (!cmd->cmd_args[0])
		return (0);
	while (cmd->cmd_args[i])
	{
		ft_unsetenv(env_list, cmd->cmd_args[i]);
		i++;
	}
	return (0);
}
