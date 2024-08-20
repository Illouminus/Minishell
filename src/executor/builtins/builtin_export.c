/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:22 by edouard           #+#    #+#             */
/*   Updated: 2024/08/20 11:03:54 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_check_var_name(const char *var_name)
{
	int i = 0;

	if (!ft_isalpha(var_name[i]) && var_name[i] != '_')
		return 1;

	i++;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return 1;
		i++;
	}
	return 0;
}

static int ft_export_error(const char *var_name)
{
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd((char *)var_name, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return 1;
}

static int ft_split_variable(char *var, char **var_name, char **var_value)
{
	*var_value = ft_strchr(var, '=');
	if (*var_value)
	{
		*var_name = ft_strndup(var, *var_value - var);
		(*var_value)++;
	}
	else
	{
		*var_name = ft_strdup(var);
		*var_value = NULL;
	}
	if (!(*var_name))
		return 1;
	return 0;
}

static int ft_export_variable(t_env *env_list, char *var)
{
	char *var_name = NULL;
	char *var_value = NULL;

	if (!var)
		return 1;
	if (ft_split_variable(var, &var_name, &var_value) == 1)
		return 1;
	if (ft_check_var_name(var_name) == 1)
	{
		ft_export_error(var_name);
		free(var_name);
		return 1;
	}
	if (var_value && *var_value != '\0')
	{
		char *trimmed_value = ft_strtrim(var_value, "\"\'");
		ft_setenv(&env_list, var_name, trimmed_value);
		free(trimmed_value);
	}
	else
	{
		ft_setenv(&env_list, var_name, "");
	}
	free(var_name);
	return 0;
}
int ft_builtin_export(t_command *cmd, t_env *env_list)
{
	int i = 0;

	if (!cmd->cmd_args || !cmd->cmd_args[0])
	{
		ft_print_env_list(env_list);
		return 0;
	}
	else
	{
		while (cmd->cmd_args[i])
		{
			if (ft_export_variable(env_list, cmd->cmd_args[i]))
				return 1;
			i++;
		}
	}
	return 0;
}