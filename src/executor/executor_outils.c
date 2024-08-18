/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:44:17 by edouard           #+#    #+#             */
/*   Updated: 2024/08/18 13:42:02 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void handle_error(const char *cmd, const char *error_message, int exit_code, t_shell *shell)
{
	fprintf(stderr, "minishell: %s: %s\n", cmd, error_message);
	shell->last_exit_status = exit_code;
	free_shell(shell);
	exit(exit_code);
}

void ft_pipe(t_command *current, t_shell *shell)
{
	if (current->next_cmd)
	{
		if (pipe(current->shell->pipe_fds) == -1)
			handle_error("pipe", "failed to create pipe", 1, shell);
	}

	shell->last_process_id = fork();

	if (shell->last_process_id == -1)
		handle_error("fork", "failed to fork process", 1, shell);
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

static char *ft_absolute_path(char *cmd, t_shell *shell)
{
	struct stat path_stat;

	if (stat(cmd, &path_stat) == -1)
		handle_error(cmd, "No such file or directory", 127, shell);
	if (S_ISDIR(path_stat.st_mode))
		handle_error(cmd, "Is a directory", 126, shell);
	if (access(cmd, X_OK) == 0)
		return cmd;
	if (access(cmd, F_OK) == -1)
		handle_error(cmd, "No such file or directory", 127, shell);
	else
		shell->last_exit_status = 126;
	return cmd;
}

char *ft_get_path(t_command *current, t_shell *shell)
{
	t_env *path_env;
	char **split;
	char *path_part;
	char *exec;
	int i;

	if (current->cmd_value[0] == '/' || current->cmd_value[0] == '.')
		return ft_absolute_path(current->cmd_value, shell);

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
