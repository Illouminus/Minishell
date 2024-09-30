/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:48:27 by edouard           #+#    #+#             */
/*   Updated: 2024/09/30 11:07:46 by ebaillot         ###   ########.fr       */
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

void	print_message_sigquit(int is_siqquit, int *quit_printed,
		int *int_printed)
{
	if (is_siqquit && !*quit_printed)
	{
		*quit_printed = 1;
		ft_putstr_fd("\nQuit: (core dumped)\n", STDOUT_FILENO);
	}
	if (!is_siqquit && !*int_printed)
	{
		*int_printed = 1;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

void	wait_commands(t_shell *shell)
{
	int	result;
	int	quit_printed;
	int	int_printed;

	signal(SIGINT, SIG_IGN);
	result = 0;
	quit_printed = 0;
	int_printed = 0;
	while (result != -1)
	{
		result = wait(&shell->tmp_proccess_status);
		if (result == shell->last_process_id)
			shell->last_exit_status = WEXITSTATUS(shell->tmp_proccess_status);
		if (WIFSIGNALED(shell->tmp_proccess_status) && result > 0)
		{
			if (WTERMSIG(shell->tmp_proccess_status) == SIGQUIT
				&& !quit_printed)
				print_message_sigquit(1, &quit_printed, &int_printed);
			if (WTERMSIG(shell->tmp_proccess_status) == SIGINT && !int_printed)
				print_message_sigquit(0, &quit_printed, &int_printed);
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
