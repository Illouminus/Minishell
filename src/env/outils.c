/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:51:04 by edouard           #+#    #+#             */
/*   Updated: 2024/09/04 10:56:27 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env *env)
{
	free(env->env_var_name);
	free(env->env_value);
	free(env);
}

void	free_env_var_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next_env;
		free_env_node(current);
		current = next;
	}
}

t_env	*ft_get_env_var_by_name(t_env *head, const char *name)
{
	while (head != NULL)
	{
		if (ft_strcmp(head->env_var_name, name) == 0)
			return (head);
		head = head->next_env;
	}
	return (NULL);
}
