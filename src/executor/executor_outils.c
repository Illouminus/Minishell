/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:44:17 by edouard           #+#    #+#             */
/*   Updated: 2024/09/03 14:44:42 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(const char *cmd, const char *error_message, int exit_code,
		t_shell *shell)
{
	fprintf(stderr, "minishell: %s: %s\n", cmd, error_message);
	shell->last_exit_status = exit_code;
	free_shell(shell);
	exit(exit_code);
}

static char	*ft_absolute_path(char *cmd, t_shell *shell)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
		handle_error(cmd, "No such file or directory", 127, shell);
	if (S_ISDIR(path_stat.st_mode))
		handle_error(cmd, "Is a directory", 126, shell);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (access(cmd, F_OK) == -1)
		handle_error(cmd, "No such file or directory", 127, shell);
	else
		handle_error(cmd, "Permission denied", 126, shell);
	return (NULL);
}

static char	*find_executable(char **split, char *cmd_value)
{
	char	*path_part;
	char	*exec;
	int		i;

	i = 0;
	while (split[i])
	{
		path_part = ft_strjoin(split[i], "/");
		exec = ft_strjoin(path_part, cmd_value);
		free(path_part);
		if (access(exec, F_OK) == 0)
			return (exec);
		free(exec);
		i++;
	}
	return (NULL);
}

char	*ft_get_path(t_command *current, t_shell *shell)
{
	t_env	*path_env;
	char	**split;
	char	*exec;

	if (current->cmd_value[0] == '/' || current->cmd_value[0] == '.')
		return (ft_absolute_path(current->cmd_value, shell));
	path_env = ft_get_env_var_by_name(shell->env_var_list, "PATH");
	if (!path_env)
		return (NULL);
	split = ft_split(path_env->env_value, ':');
	exec = find_executable(split, current->cmd_value);
	ft_free_array(split);
	return (exec);
}

char	**ft_construct_cmd_args(char *cmd_name, char **cmd_args)
{
	char	**args;
	int		count;
	int		count_args;
	int		i;

	count = 0;
	while (cmd_args[count])
		count++;
	args = malloc(sizeof(char *) * (count + 2));
	if (!args)
		return (NULL);
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
	return (args);
}
