/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:29:45 by edouard           #+#    #+#             */
/*   Updated: 2024/07/02 14:49:53 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_env_var_to_list(t_env **head, t_env *new_var)
{
	if (!head || !new_var)
		return;

	if (!*head)
	{
		*head = new_var;
	}
	else
	{
		t_env *current = *head;
		while (current->next_env)
			current = current->next_env;
		current->next_env = new_var;
	}
}

t_env *init_default_env_vars(void)
{
	t_env *head = NULL;
	t_env *new_var = NULL;

	new_var = create_default_env_var_node("PWD", getcwd(NULL, 0));
	if (!new_var)
		return (free_env_var_list(head), NULL);
	add_env_var_to_list(&head, new_var);

	new_var = create_default_env_var_node("SHLVL", "1");
	if (!new_var)
		return (free_env_var_list(head), NULL);
	add_env_var_to_list(&head, new_var);

	new_var = create_default_env_var_node("_", "/usr/bin/env");
	if (!new_var)
		return (free_env_var_list(head), NULL);
	add_env_var_to_list(&head, new_var);

	return head;
}

t_env *create_default_env_var_node(char *var_name, char *value)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return NULL;

	node->env_var_name = strdup(var_name);
	node->env_value = strdup(value);
	node->next_env = NULL;
	return node;
}

t_env *create_env_var_node(char *env_str)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return NULL;

	char *delimiter_pos = strchr(env_str, '=');
	if (delimiter_pos)
	{
		size_t name_len = delimiter_pos - env_str;
		node->env_var_name = strndup(env_str, name_len);
		node->env_value = strdup(delimiter_pos + 1);
	}
	else
	{
		node->env_var_name = strdup(env_str);
		node->env_value = NULL;
	}
	node->next_env = NULL;
	return node;
}