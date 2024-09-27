/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:22:12 by edouard           #+#    #+#             */
/*   Updated: 2024/09/27 14:29:32 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtins(t_command *current, t_shell *shell, bool is_main_shell)
{
	if (ft_strcmp(current->cmd_value, "echo") == 0)
		shell->last_exit_status = ft_builtin_echo(current);
	else if (ft_strcmp(current->cmd_value, "cd") == 0)
		shell->last_exit_status = ft_builtin_cd(current, shell);
	else if (ft_strcmp(current->cmd_value, "pwd") == 0)
		shell->last_exit_status = ft_builtin_pwd(current);
	else if (ft_strcmp(current->cmd_value, "export") == 0)
		shell->last_exit_status = ft_builtin_export(current,
				&shell->env_var_list);
	else if (ft_strcmp(current->cmd_value, "unset") == 0)
		shell->last_exit_status = ft_builtin_unset(current,
				&shell->env_var_list);
	else if (ft_strcmp(current->cmd_value, "env") == 0)
		shell->last_exit_status = ft_builtin_env(shell->env_var_list);
	else if (ft_strcmp(current->cmd_value, "exit") == 0)
		ft_builtin_exit(current, shell, is_main_shell);
}

static void	ft_execute_command(t_command *current, t_shell *shell,
		bool is_main_shell)
{
	signal(SIGQUIT, SIG_DFL);
	ft_check_empty_command(current, shell);
	if (!ft_execute_builtin_if_needed(current, shell, is_main_shell))
		ft_execute_external_command(current, shell);
}

static void	ft_child_process(t_command *current, t_shell *shell, int prev_fd)
{
	handle_redirections(current, prev_fd);
	ft_execute_command(current, shell, false);
	exit(shell->last_exit_status);
}

int	ft_parent_process(t_command *current, int prev_fd)
{
	if (prev_fd != 0)
		close(prev_fd);
	if (current->next_cmd)
	{
		close(current->shell->pipe_fds[1]);
		prev_fd = current->shell->pipe_fds[0];
	}
	return (prev_fd);
}

int	ft_executor(t_shell *shell)
{
	t_command	*current;
	int			prev_fd;

	if (shell->command_list == NULL)
		return (0);
	current = shell->command_list;
	prev_fd = 0;
	if (!current->next_cmd && current->is_builtin_cmd && !current->redirections)
		ft_exec_builtins(current, shell, true);
	else
	{
		while (current)
		{
			ft_pipe(current, shell);
			if (shell->last_process_id == 0)
				ft_child_process(current, shell, prev_fd);
			else
				prev_fd = ft_parent_process(current, prev_fd);
			current = current->next_cmd;
		}
	}
	wait_commands(shell);
	free_shell(shell);
	return (shell->last_exit_status);
}
