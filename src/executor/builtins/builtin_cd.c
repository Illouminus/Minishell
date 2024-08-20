/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:13 by edouard           #+#    #+#             */
/*   Updated: 2024/08/20 10:49:28 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handle_cd_error(const char *cmd, const char *error_message, t_shell *shell, char *s1, char *s2)
{
	handle_error(cmd, error_message, 1, shell);
	free(s1);
	free(s2);
	return 1;
}

void ft_update_pwd(t_shell *shell, const char *command)
{
	char cwd[4096];
	char *old_dir;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		handle_error(command, strerror(errno), 1, shell);
		return;
	}

	old_dir = ft_getenv(shell->env_var_list, "PWD");
	if (!old_dir)
		return;

	ft_setenv(&shell->env_var_list, "OLDPWD", old_dir);
	free(old_dir);
	ft_setenv(&shell->env_var_list, "PWD", cwd);
}

int ft_fd_minus(t_shell *shell, int option)
{
	char *curr_dir = ft_getenv(shell->env_var_list, "OLDPWD");
	char *old_dir = ft_getenv(shell->env_var_list, "PWD");

	if (!curr_dir)
		return handle_cd_error("cd", "OLDPWD not set", shell, curr_dir, old_dir);

	if (!old_dir)
		return handle_cd_error("cd", "PWD not set", shell, curr_dir, old_dir);

	if (chdir(curr_dir) == -1)
		return handle_cd_error("cd", strerror(errno), shell, curr_dir, old_dir);

	if (option == 1)
	{
		ft_putstr_fd(curr_dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}

	ft_setenv(&shell->env_var_list, "OLDPWD", old_dir);
	ft_setenv(&shell->env_var_list, "PWD", curr_dir);

	free(curr_dir);
	free(old_dir);
	return 0;
}

int check_for_arguments(t_command *commands, t_shell *shell)
{
	if (commands->cmd_args[0])
	{
		if (ft_strcmp(commands->cmd_args[0], "-") == 0)
			return ft_fd_minus(shell, 1);
		else if (ft_strcmp(commands->cmd_args[0], "--") == 0)
			return ft_fd_minus(shell, 0);
		else if (chdir(commands->cmd_args[0]) == -1)
		{
			handle_error("cd", strerror(errno), 1, shell);
			return 1;
		}

		ft_update_pwd(shell, commands->cmd_args[0]);
	}
	return 0;
}

int ft_builtin_cd(t_command *cmd, t_shell *shell)
{
	char *value;

	if (!cmd->cmd_args[0])
	{
		value = ft_getenv(shell->env_var_list, "HOME");
		if (!value)
			return handle_cd_error("cd", "HOME not set", shell, NULL, NULL);
		if (ft_strlen(value) == 0)
		{
			free(value);
			value = getcwd(NULL, 0);
			if (!value)
				return handle_cd_error("cd", "getcwd failed", shell, NULL, NULL);
		}
		if (chdir(value) == -1)
		{
			int ret = handle_cd_error("cd", strerror(errno), shell, value, NULL);
			free(value);
			return ret;
		}
		ft_update_pwd(shell, value);
		free(value);
		return 0;
	}
	return check_for_arguments(cmd, shell);
}
