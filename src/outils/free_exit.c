/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:15:23 by edouard           #+#    #+#             */
/*   Updated: 2024/07/18 14:15:10 by edouard          ###   ########.fr       */
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
	if (shell)
	{
		if (shell->heredoc_tempfile)
		{
			free(shell->heredoc_tempfile);
			shell->heredoc_tempfile = NULL;
		}
		// if (shell->token_list)
		// 	free_tokens(&(shell->token_list));
		// if (shell->command_list)
		// 	free_commands(&(shell->command_list));
	}
}