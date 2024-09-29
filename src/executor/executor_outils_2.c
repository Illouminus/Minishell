/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_outils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:18:50 by ebaillot          #+#    #+#             */
/*   Updated: 2024/09/28 17:48:31 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_check_empty_command(t_command *current, t_shell *shell, int prev_fd)
{
	(void)prev_fd;
	if (current->cmd_value == NULL || ft_strlen(current->cmd_value) == 0)
	{
		shell->last_exit_status = 0;
		free_shell(shell);
		exit(shell->last_exit_status);
	}
}

bool ft_execute_builtin_if_needed(t_command *current, t_shell *shell,
											 bool is_main_shell)
{
	if (current->is_builtin_cmd)
	{
		ft_exec_builtins(current, shell, is_main_shell);
		return (true);
	}
	return (false);
}

void ft_execute_external_command(t_command *current, t_shell *shell)
{
	char *path;
	char **cmd_args;
	char **env_array;

	env_array = convert_env_list_to_array(shell->env_var_list);
	path = ft_get_path(current, shell);
	if (!path)
		handle_error(current->cmd_value, "command not found", 127, shell);
	cmd_args = ft_construct_cmd_args(current->cmd_value, current->cmd_args);
	if (execve(path, cmd_args, env_array) == -1)
	{
		free(path);
		ft_free_array(cmd_args);
		ft_free_array(env_array);
		handle_error(current->cmd_value, strerror(errno), 1, shell);
	}
	ft_free_array(env_array);
}
