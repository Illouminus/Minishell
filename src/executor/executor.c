/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:22:12 by edouard           #+#    #+#             */
/*   Updated: 2024/07/25 12:20:11 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exec_builtins(t_shell *shell)
{
	t_command *current = shell->command_list;

	if (ft_strcmp(current->cmd_name, "echo") == 0)
		shell->last_exit_status = ft_builtin_echo(current);
	else if (ft_strcmp(current->cmd_name, "cd") == 0)
		shell->last_exit_status = ft_builtin_cd(current, shell);
	else if (ft_strcmp(current->cmd_name, "pwd") == 0)
		shell->last_exit_status = ft_builtin_pwd(current);
	else if (ft_strcmp(current->cmd_name, "export") == 0)
		shell->last_exit_status = ft_builtin_export(current, shell);
	else if (ft_strcmp(current->cmd_name, "unset") == 0)
		shell->last_exit_status = ft_builtin_export(current, shell);
	else if (ft_strcmp(current->cmd_name, "env") == 0)
		shell->last_exit_status = ft_builtin_env(current);
	else if (ft_strcmp(current->cmd_name, "exit") == 0)
		shell->last_exit_status = ft_builtin_exit(current);
}

void ft_child_process(t_command *current, t_shell *shell, int prev_fd)
{
	if (current->redir_tokens)
	{
		// TODO handle redirections
	}
	ft_redirect_input(current, shell, prev_fd);
	ft_execute_command(current, shell);
}

int ft_executor(t_shell *shell)
{
	t_command *current;
	int prev_fd;
	if (shell->command_list == NULL)
		return -1;
	current = shell->command_list;
	prev_fd = 0;

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
		while (current)
		{
			ft_pipe(current, shell);

			if (shell->last_process_id == 0)
				ft_child_process(current, shell, prev_fd);
			else
				prev_fd = ft_parent_process(current, shell);
			if (current->next_cmd)
				current = current->next_cmd;
		}
	}
	return 0;
}
