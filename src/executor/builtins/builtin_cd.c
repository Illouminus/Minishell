/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:13 by edouard           #+#    #+#             */
/*   Updated: 2024/07/24 11:20:00 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int free_and_return(char *s1, char *s2, int ret)
{
	free(s1);
	free(s2);
	return ret;
}

void ft_update_pwd(t_shell *shell, const char *command)
{
	char cwd[4096];
	char *old_dir;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(command);
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
	{
		print_error("cd", "OLDPWD not set");
		return free_and_return(curr_dir, old_dir, 1);
	}
	else if (!old_dir)
	{
		print_error("cd", "PWD not set");
		return free_and_return(curr_dir, old_dir, 1);
	}
	if (chdir(curr_dir) == -1)
	{
		perror("cd");
		return free_and_return(curr_dir, old_dir, 1);
	}
	if (option == 1)
	{
		ft_putstr_fd(curr_dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	ft_setenv(&shell->env_var_list, "PWD", curr_dir);
	ft_setenv(&shell->env_var_list, "OLDPWD", old_dir);
	return free_and_return(curr_dir, old_dir, 0);
}

int check_for_arguments(t_command *commands, t_shell *shell)
{
	if (commands->cmd_args[1])
	{
		if (commands->cmd_args[1][0] == '-' && !commands->cmd_args[1][1])
			return ft_cd_minus(shell, 1);
		else if (commands->cmd_args[1][0] == '-' && commands->cmd_args[1][1] == '-' && !commands->cmd_args[1][2])
			return ft_cd_minus(shell, 0);
		else if (commands->cmd_args[1][0] == '-' && commands->cmd_args[1][1])
		{
			print_error("cd", "invalid option");
			return 2;
		}
		else if (chdir(commands->cmd_args[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			perror(commands->cmd_args[1]);
			return 1;
		}
		ft_update_pwd(shell, commands->cmd_args[1]);
	}
	return 0;
}

int ft_builtin_cd(t_command *cmd, t_shell *shell)
{
	char *value;

	if (cmd->cmd_args[2])
		print_error("cd", "too many arguments");
	return 1;

	if (!cmd->cmd_args[1])
	{
		value = ft_getenv(shell->env_var_list, "HOME");
		if (!value)
		{
			print_error("cd", "HOME not set");
			return 1;
		}
		if (ft_strlen(value) == 0)
		{
			free(value);
			value = getcwd(NULL, 0);
			if (!value)
			{
				print_error("cd", "getcwd failed");
				return 1;
			}
		}
		if (chdir(value) == -1)
		{
			perror("minishell: cd");
			free(value);
			return 1;
		}
		ft_update_pwd(shell, cmd->cmd_args[0]);
		free(value);
	}
	return check_for_arguments(cmd, shell);
}
