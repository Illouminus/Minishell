/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:22:12 by edouard           #+#    #+#             */
/*   Updated: 2024/07/24 11:22:56 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exec_builtins(t_shell *shell)
{
	t_command *current = shell->command_list;

	if (ft_strcmp(current->cmd_name, "echo") == 0)
		ft_builtin_echo(current);
	else if (ft_strcmp(current->cmd_name, "cd") == 0)
		ft_builtin_cd(current, shell);
	else if (ft_strcmp(current->cmd_name, "pwd") == 0)
		ft_builtin_pwd(current);
	else if (ft_strcmp(current->cmd_name, "export") == 0)
		ft_builtin_export(current, shell);
	else if (ft_strcmp(current->cmd_name, "unset") == 0)
		ft_builtin_export(current, shell);
	else if (ft_strcmp(current->cmd_name, "env") == 0)
		ft_builtin_env(current);
	else if (ft_strcmp(current->cmd_name, "exit") == 0)
		ft_builtin_exit(current);
}

int ft_executor(t_shell *shell)
{
	t_command *current;

	if (shell->command_list == NULL)
		return -1;
	current = shell->command_list;
	// TODO if builtin is exit check redirections not next value end execute exit builtin

	if (!current->next_cmd && !current->is_builtin_cmd)
	{
		// TODO execute command because it's just one command
	}
	else if (!current->next_cmd && current->is_builtin_cmd)
	{
		// TODO execute builtin command because it's just one command and it's a builtin
	}
	else
	{
		// TODO execute command with pipes
	}
	return 0;
}