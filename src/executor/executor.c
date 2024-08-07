/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:22:12 by edouard           #+#    #+#             */
/*   Updated: 2024/08/07 12:38:07 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_execute_command(t_command *current, t_shell *shell, char **env)
{
	char *path;
	char **cmd_args;
	signal(SIGQUIT, SIG_DFL);
	path = ft_get_path(current, shell);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(current->cmd_value, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	cmd_args = ft_construct_cmd_args(current->cmd_value, current->cmd_args);
	if (execve(path, cmd_args, env) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(current->cmd_value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(1);
	}
}

void ft_exec_builtins(t_shell *shell)
{
	t_command *current = shell->command_list;

	if (ft_strcmp(current->cmd_value, "echo") == 0)
		shell->last_exit_status = ft_builtin_echo(current);
	else if (ft_strcmp(current->cmd_value, "cd") == 0)
		shell->last_exit_status = ft_builtin_cd(current, shell);
	else if (ft_strcmp(current->cmd_value, "pwd") == 0)
		shell->last_exit_status = ft_builtin_pwd(current);
	else if (ft_strcmp(current->cmd_value, "export") == 0)
		shell->last_exit_status = ft_builtin_export(current, shell->env_var_list);
	else if (ft_strcmp(current->cmd_value, "unset") == 0)
		shell->last_exit_status = ft_builtin_export(current, shell->env_var_list);
	else if (ft_strcmp(current->cmd_value, "env") == 0)
		shell->last_exit_status = ft_builtin_env(shell->env_var_list);
	else if (ft_strcmp(current->cmd_value, "exit") == 0)
		shell->last_exit_status = ft_builtin_exit();
}

static void ft_child_process(t_command *current, t_shell *shell, int prev_fd, char **env)
{
	handle_redirections(current, prev_fd);
	ft_execute_command(current, shell, env);
}

int ft_parent_process(t_command *current, t_shell *shell, int prev_fd)
{

	waitpid(shell->last_process_id, NULL, 0);
	if (prev_fd != 0)
		close(prev_fd);
	if (current->next_cmd)
	{
		close(current->pipe_fds[1]);
		prev_fd = current->pipe_fds[0];
	}
	return prev_fd;
}

int ft_executor(t_shell *shell, char **env)
{
	t_command *current;
	int prev_fd;
	if (shell->command_list == NULL)
		return -1;
	current = shell->command_list;
	prev_fd = 0;

	if (!current->next_cmd && current->is_builtin_cmd)
		ft_exec_builtins(shell);
	else
	{
		while (current)
		{
			printf("Command: %s\n", current->cmd_value);
			ft_pipe(current, shell);
			if (shell->last_process_id == 0)
				ft_child_process(current, shell, prev_fd, env);
			else
				prev_fd = ft_parent_process(current, shell, prev_fd);
			current = current->next_cmd;
		}
	}
	return 0;
}
