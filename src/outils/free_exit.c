/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:15:23 by edouard           #+#    #+#             */
/*   Updated: 2024/08/02 11:18:40 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_env_node(t_env *env)
{
	free(env->env_var_name);
	free(env->env_value);
	free(env);
}

void free_env_var_list(t_env *env)
{
	t_env *current;
	t_env *next;

	current = env;
	while (current)
	{
		next = current->next_env;
		free_env_node(current);
		current = next;
	}
}

void global_exit_env(t_shell *shell, int status)
{
	if (shell)
	{
		if (shell->env_var_list)
			free_env_var_list(shell->env_var_list);
	}
	clear_history();
	exit(status);
}

void free_shell(t_shell *shell)
{
	// Очистка списка команд
	t_command *cmd_temp;
	char **args;
	while (shell->command_list)
	{
		cmd_temp = shell->command_list;
		shell->command_list = shell->command_list->next_cmd;
		free(cmd_temp->cmd_name);
		args = cmd_temp->cmd_args;
		while (*args)
		{
			free(*args);
			args++;
		}
		free(cmd_temp->cmd_args);
		free(cmd_temp);
	}

	// Очистка списка токенов
	t_token *tok_temp;
	while (shell->token_list)
	{
		tok_temp = shell->token_list;
		shell->token_list = shell->token_list->next_tok;
		free(tok_temp->tok_value);
		free(tok_temp);
	}

	// Очистка пользовательского ввода
	if (shell->user_input)
	{
		free(shell->user_input);
		shell->user_input = NULL;
	}
}