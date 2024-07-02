/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:33:56 by edouard           #+#    #+#             */
/*   Updated: 2024/07/02 14:34:16 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env_var_list(t_env *head)
{
	t_env *tmp;
	while (head)
	{
		tmp = head;
		head = head->next_env;
		free(tmp->env_var_name);
		free(tmp->env_value);
		free(tmp);
	}
}
