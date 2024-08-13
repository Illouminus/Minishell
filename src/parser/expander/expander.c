/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:03:53 by edouard           #+#    #+#             */
/*   Updated: 2024/08/12 15:41:03 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expander(char *str, t_shell *shell)
{
	t_env *env_var;

	env_var = ft_get_env_var_by_name(shell->env_var_list, var_name);
	if (env_var)
		return env_var->env_value;
	return NULL;
}

int estimate_final_length(const char *str, t_shell *shell)
{
	int len;
	int i;
	char *var_name;
	char *env_value;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_var_char(str[i + 1]))
		{
			i++;
			var_name = extract_var_name(str, &i);
			env_value = get_env_value(var_name, shell);
			if (env_value)
				len += ft_strlen(env_value);
			free(var_name);
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return result;
}