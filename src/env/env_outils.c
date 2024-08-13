/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_outils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:29:45 by edouard           #+#    #+#             */
/*   Updated: 2024/08/08 17:41:14 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_env_var_to_list(t_env **head, t_env *new_var)
{

	t_env *current;

	if (!new_var)
		return;

	if (*head == NULL)
		*head = new_var;
	else
	{
		current = *head;
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

	node->env_var_name = ft_strdup(var_name);
	node->env_value = ft_strdup(value);
	node->next_env = NULL;
	return node;
}

t_env *create_env_var_node(char *env_str)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return NULL;

	char *delimiter_pos = ft_strchr(env_str, '=');
	if (delimiter_pos)
	{
		size_t name_len = delimiter_pos - env_str;
		node->env_var_name = ft_strndup(env_str, name_len);
		node->env_value = ft_strdup(delimiter_pos + 1);
	}
	else
	{
		node->env_var_name = ft_strdup(env_str);
		node->env_value = NULL;
	}
	node->next_env = NULL;
	return node;
}

t_env *ft_get_env_var_by_name(t_env *head, const char *name)
{
	while (head != NULL)
	{
		if (ft_strcmp(head->env_var_name, name) == 0)
			return head;
		head = head->next_env;
	}
	return NULL;
}
