/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:03:53 by edouard           #+#    #+#             */
/*   Updated: 2024/08/08 14:27:09 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_expander(char *str, t_shell *shell)
{
	int i = 0;
	int len = ft_strlen(str);
	char *result = malloc(len + 1);
	t_env *env_var;
	char *env_value;
	int j = 0;

	while (i < len)
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			int start = i + 1;
			while (i < len && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			char *var_name = ft_substr(str, start, i - start);
			env_var = ft_get_env_var_by_name(shell->env_var_list, var_name);
			env_value = env_var ? env_var->env_value : NULL;
			if (env_value)
			{
				while (*env_value)
					result[j++] = *env_value++;
			}
			free(var_name);
		}
		else
			return (ft_strdup(str)); 
	}
	result[j] = '\0';
	free(str);
	return result;
}
