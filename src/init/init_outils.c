/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:50:38 by edouard           #+#    #+#             */
/*   Updated: 2024/07/02 14:35:34 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_shell(t_shell *shell, char **env)
{
	(void)env;
	shell->env_var_list = init_env_vars(env);
	if (shell->env_var_list == NULL)
		return (1);

	shell->token_list = NULL;
	shell->command_list = NULL;
	shell->last_process_id = -2;
	shell->input_fd = -2;
	shell->output_fd = -2;
	shell->pipe_fds[0] = -2;
	shell->pipe_fds[1] = -2;
	shell->last_exit_status = 0;
	shell->heredoc_tempfile = NULL;
	shell->saved_stdin_fd = -1;
	shell->user_input = NULL;
	shell->command_path = NULL;

	return (0);
}

t_env *init_env_vars(char **env)
{
	if (!env || !*env)
		return init_default_env_vars();

	t_env *head = NULL;
	t_env *new_var = NULL;
	int i = 0;

	while (env[i])
	{
		new_var = create_env_var_node(env[i]);
		if (!new_var)
		{
			free_env_var_list(head);
			return NULL;
		}
		add_env_var_to_list(&head, new_var);
		i++;
	}

	return head;
}