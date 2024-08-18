/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:48:27 by edouard           #+#    #+#             */
/*   Updated: 2024/08/15 10:21:41 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(char *cmd, char *error_message)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

char *ft_getenv(t_env *env_list, const char *name)
{
	t_env *var = ft_get_env_var_by_name(env_list, name);
	if (var)
	{
		return strdup(var->env_value);
	}
	return NULL;
}

void ft_setenv(t_env **env_list, const char *name, const char *value)
{
	t_env *var = ft_get_env_var_by_name(*env_list, name);
	if (var)
	{
		free(var->env_value);
		var->env_value = strdup(value);
	}
	else
	{
		t_env *new_var = malloc(sizeof(t_env));
		if (new_var)
		{
			new_var->env_var_name = strdup(name);
			new_var->env_value = strdup(value);
			new_var->next_env = *env_list;
			*env_list = new_var;
		}
	}
}

// Функция для обработки сигнала завершения процесса
/*static void handle_exit_status(t_shell *shell)
{
	if (WIFEXITED(shell->tmp_proccess_status))
	{
		// Процесс завершился нормально, сохраняем код завершения
		shell->last_exit_status = WEXITSTATUS(shell->tmp_proccess_status);
	}
	else if (WIFSIGNALED(shell->tmp_proccess_status))
	{
		// Процесс завершился по сигналу
		shell->last_exit_status = 128 + WTERMSIG(shell->tmp_proccess_status);

		// Обработка конкретных сигналов
		if (shell->last_exit_status == 131)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		}
		else if (shell->last_exit_status == 139)
		{
			ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
		}
		else if (shell->last_exit_status == 130)
		{
			ft_putstr_fd("\n", STDERR_FILENO); // SIGINT (Ctrl+C)
		}
	}
}
*/

// Функция ожидания завершения всех дочерних процессов
/*void wait_commands(t_shell *shell)
{
	signal(SIGINT, SIG_IGN); // Игнорируем сигнал SIGINT (Ctrl+C) во время ожидания

	int wait_result;
	while ((wait_result = wait(&shell->tmp_proccess_status)) != -1 || errno != ECHILD)
	{
		if (wait_result == shell->tmp_proccess_status)
		{
			handle_exit_status(shell);
		}
	}

	// Если глобальный код завершения равен 130 (обычно SIGINT), устанавливаем его как статус завершения
	if (g_exit_code == 130)
	{
		shell->last_exit_status = 130;
	}
}*/
void wait_commands(t_shell *shell)
{
	signal(SIGINT, SIG_IGN);
	int result;

	while (errno != ECHILD)
	{
		result = wait(&shell->tmp_proccess_status);
		if (result == shell->last_process_id)
		{
			if (WIFEXITED(shell->tmp_proccess_status))
			{
				shell->last_exit_status = WEXITSTATUS(shell->tmp_proccess_status);
			}
			else
			{
				shell->last_exit_status = 128 + WTERMSIG(shell->tmp_proccess_status);
				if (shell->last_exit_status == 131)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				else if (shell->last_exit_status == 139)
					ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
			}
			if (shell->last_exit_status == 130)
				ft_putstr_fd("\n", STDERR_FILENO);
		}
	}

	if (g_exit_code == 130)
		shell->last_exit_status = 130;
}