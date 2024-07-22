/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:22 by edouard           #+#    #+#             */
/*   Updated: 2024/07/22 14:36:08 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_print_env_list(t_env *env_list)
{
	t_env *current = env_list;
	while (current)
	{
		ft_putstr_fd(current->env_var_name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(current->env_value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next_env;
	}
}

static int ft_check_var_name(char *var_name)
{
	int i;

	i = 0;
	if (!ft_isalpha(var_name[i]) && var_name[i] != '_')
	{
		return 1;
	}
	i++;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(var_name, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return 1;
		}
		i++;
	}
	return 0;
}

static void ft_export_variable(t_env *env_list, char *var)
{
	char *var_name;
	char *var_value;
	t_env *current;

	var_name = ft_strndup(var, ft_strchr(var, '=') - var);
	if (!var_name || ft_check_var_name(var_name) == 1)
	{
		free(var_name);
		return;
	}
	var_value = ft_strchr(var, '=') + 1;
}

int ft_builtin_export(t_command *cmd, t_env *env_list)
{
	int i;

	i = 0;
	// TODO : Gérer les erreurs de cmd (NULL, pas de cmd_args, etc)

	if (!cmd->cmd_args)
	{
		ft_print_env_list(env_list);
		return 0;
	}
	else
	{
		while (cmd->cmd_args[i])
		{
			ft_export_variable(env_list, cmd->cmd_args[i]);
			i++;
		}
	}
	return 0;
}