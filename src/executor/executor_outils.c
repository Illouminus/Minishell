/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:44:17 by edouard           #+#    #+#             */
/*   Updated: 2024/08/07 12:28:42 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit_error(t_shell *shell, char *error_message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->last_exit_status = 1;
	exit(1);
}

void ft_pipe(t_command *current, t_shell *shell)
{
	if (current->next_cmd)
	{
		if (pipe(current->pipe_fds) == -1)
			ft_exit_error(shell, "pipe failed"); // TODO: handle error
		else
		{
			printf("Pipe created: %d, %d\n", current->pipe_fds[0], current->pipe_fds[1]);
		}
	}
	shell->last_process_id = fork();

	if (shell->last_process_id == -1)
		ft_exit_error(shell, "fork failed"); // TODO: handle error
}

void ft_free_array(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char *ft_get_path(t_command *current, t_shell *shell)
{
	t_env *path_env;
	char **split;
	char *path_part;
	char *exec;
	int i;

	path_env = ft_get_env_var_by_name(shell->env_var_list, "PATH");
	split = ft_split(path_env->env_value, ':');
	i = 0;

	while (split[i])
	{
		path_part = ft_strjoin(split[i], "/");
		exec = ft_strjoin(path_part, current->cmd_value);
		free(path_part);
		if (access(exec, F_OK) == 0)
		{
			ft_free_array(split);
			return exec;
		}
		i++;
	}
	ft_free_array(split);
	return NULL;
}

char **ft_construct_cmd_args(char *cmd_name, char **cmd_args)
{
	char **args;
	int count;
	int count_args;
	int i;

	count = 0;

	while (cmd_args[count])
		count++;
	args = malloc(sizeof(char *) * (count + 2));
	if (!args)
		return NULL;
	args[0] = ft_strdup(cmd_name);
	count_args = 1;
	i = 0;
	while (count_args <= count)
	{
		args[count_args] = ft_strdup(cmd_args[i]);
		count_args++;
		i++;
	}
	args[count_args] = NULL;
	return args;
}
