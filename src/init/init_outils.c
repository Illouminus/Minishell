/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:50:38 by edouard           #+#    #+#             */
/*   Updated: 2024/08/20 09:54:12 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_shell(t_shell *shell, char **env)
{
	shell->env_var_list = init_env_vars(env);
	if (shell->env_var_list == NULL)
		return (1);

	shell->token_list = NULL;
	shell->command_list = NULL;
	shell->last_process_id = -2;
	shell->last_exit_status = 0;
	shell->heredoc_tempfile = NULL;
	shell->user_input = NULL;
	shell->heredoc_tempfile = ft_strdup("heredoc_tempfile");
	shell->pipe_fds[0] = -2;
	shell->pipe_fds[1] = -2;
	return (0);
}
void print_env_vars(t_env *head)
{
	while (head)
	{
		printf("Variable: %s=%s\n", head->env_var_name, head->env_value);
		head = head->next_env;
	}
}

t_env *init_env_vars(char **env)
{

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
	// add_env_var_to_list(&head, NULL);
	if (!head)
		head = init_default_env_vars();
	// print_env_vars(head);
	return head;
}