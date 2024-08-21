/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:22:12 by edouard           #+#    #+#             */
/*   Updated: 2024/08/21 12:11:10 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exec_builtins(t_shell *shell, bool next_cmd)
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
		shell->last_exit_status = ft_builtin_unset(current, &shell->env_var_list);
	else if (ft_strcmp(current->cmd_value, "env") == 0)
		shell->last_exit_status = ft_builtin_env(shell->env_var_list);
	else if (ft_strcmp(current->cmd_value, "exit") == 0)
		ft_builtin_exit(current, shell);
	if (next_cmd)
		free_shell(shell);
}

static void ft_execute_command(t_command *current, t_shell *shell, char **env)
{
	char *path;
	char **cmd_args;

	signal(SIGQUIT, SIG_DFL);
	if (current->cmd_value == NULL || ft_strlen(current->cmd_value) == 0)
	{
		shell->last_exit_status = 0;
		free_shell(shell);
		exit(shell->last_exit_status);
	}
	if (current->is_builtin_cmd && current->next_cmd)
		ft_exec_builtins(shell, true);
	else
	{
		path = ft_get_path(current, shell);
		if (!path)
			handle_error(current->cmd_value, "command not found", 127, shell);
		cmd_args = ft_construct_cmd_args(current->cmd_value, current->cmd_args);
		if (execve(path, cmd_args, env) == -1)
		{
			free(path);
			ft_free_array(cmd_args);
			handle_error(current->cmd_value, strerror(errno), 1, shell);
		}
	}
}

static void ft_child_process(t_command *current, t_shell *shell, int prev_fd, char **env)
{
	handle_redirections(current, prev_fd);
	ft_execute_command(current, shell, env);
	free_shell(shell);
	exit(shell->last_exit_status);
}

int ft_parent_process(t_command *current, int prev_fd)
{
	if (prev_fd != 0)
		close(prev_fd);
	if (current->next_cmd)
	{
		close(current->shell->pipe_fds[1]);
		prev_fd = current->shell->pipe_fds[0];
	}
	return prev_fd;
}

int ft_executor(t_shell *shell, char **env)
{
	t_command *current;
	int prev_fd;
	if (shell->command_list == NULL)
		return 0;
	current = shell->command_list;
	prev_fd = 0;

	if (!current->next_cmd && current->is_builtin_cmd && !current->redirections)
		ft_exec_builtins(shell, false);
	else
	{
		while (current)
		{
			ft_pipe(current, shell);
			if (shell->last_process_id == 0)
				ft_child_process(current, shell, prev_fd, env);
			else
				prev_fd = ft_parent_process(current, prev_fd);
			current = current->next_cmd;
		}
	}
	wait_commands(shell);
	return shell->last_exit_status;
}
