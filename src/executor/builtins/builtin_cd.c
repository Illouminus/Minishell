/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:13 by edouard           #+#    #+#             */
/*   Updated: 2024/09/22 11:11:39 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Функция для получения домашнего каталога
static char *get_home_directory(t_shell *shell)
{
	char *home;

	home = ft_getenv(shell->env_var_list, "HOME");
	if (!home)
	{
		handle_error_non_critical("cd", "HOME not set", 1, shell);
		return NULL;
	}
	if (ft_strlen(home) == 0)
	{
		free(home);
		home = ft_getenv(shell->env_var_list, "PWD");
		if (!home)
		{
			handle_error_non_critical("cd", "PWD not set", 1, shell);
			return NULL;
		}
	}
	return home;
}

static int change_directory(const char *path, t_shell *shell)
{
	if (chdir(path) == -1)
	{
		handle_error_non_critical("cd", ft_strdup(strerror(errno)), 1, shell);
		return 1;
	}
	ft_update_pwd(shell, path);
	return 0;
}

static int handle_cd_no_arguments(t_shell *shell)
{
	char *home;

	home = get_home_directory(shell);
	if (!home)
		return 1;
	int result = change_directory(home, shell);
	free(home);
	return result;
}

int check_for_arguments(t_command *commands, t_shell *shell)
{
	if (commands->cmd_args[1])
	{
		return handle_cd_error((t_error_info){"cd", "too many arguments", 1}, shell, NULL, NULL);
	}
	if (commands->cmd_args[0])
	{
		if (ft_strcmp(commands->cmd_args[0], "-") == 0)
			return ft_fd_minus(shell, 1);
		else if (ft_strcmp(commands->cmd_args[0], "--") == 0)
			return ft_fd_minus(shell, 0);
		else
		{
			if (change_directory(commands->cmd_args[0], shell) != 0)
				return 1;
		}
	}
	return 0;
}

int ft_builtin_cd(t_command *cmd, t_shell *shell)
{
	if (!cmd->cmd_args[0])
		return handle_cd_no_arguments(shell);
	return check_for_arguments(cmd, shell);
}