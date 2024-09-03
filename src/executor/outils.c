/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:48:27 by edouard           #+#    #+#             */
/*   Updated: 2024/09/03 14:02:39 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_getenv(t_env *env_list, const char *name)
{
	t_env	*var;

	var = ft_get_env_var_by_name(env_list, name);
	if (var)
	{
		return (strdup(var->env_value));
	}
	return (NULL);
}

void	ft_setenv(t_env **env_list, const char *name, const char *value)
{
	t_env	*var;
	t_env	*new_var;

	var = ft_get_env_var_by_name(*env_list, name);
	if (var)
	{
		free(var->env_value);
		var->env_value = strdup(value);
	}
	else
	{
		new_var = malloc(sizeof(t_env));
		if (!new_var)
			return ;
		if (new_var)
		{
			new_var->env_var_name = strdup(name);
			new_var->env_value = strdup(value);
			new_var->next_env = *env_list;
			*env_list = new_var;
		}
	}
}

void	wait_commands(t_shell *shell)
{
	int	result;

	signal(SIGINT, SIG_IGN);
	result = 0;
	while (result != -1)
	{
		result = waitpid(-1, &shell->tmp_proccess_status, 0);
		if (result == shell->last_process_id)
		{
			if (WIFEXITED(shell->tmp_proccess_status))
				shell->last_exit_status = WEXITSTATUS(
						shell->tmp_proccess_status);
			else
				shell->last_exit_status = 128
					+ WTERMSIG(shell->tmp_proccess_status);
		}
		else if (result == -1 && errno != ECHILD)
		{
			perror("waitpid error");
			break ;
		}
	}
	if (g_exit_code == 130)
		shell->last_exit_status = 130;
}

void	ft_print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		ft_putstr_fd(current->env_var_name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(current->env_value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next_env;
	}
}
