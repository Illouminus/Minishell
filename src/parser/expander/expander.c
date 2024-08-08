/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:03:53 by edouard           #+#    #+#             */
/*   Updated: 2024/08/08 17:42:11 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(const char *var_name, t_shell *shell)
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
			len++;
			i++;
		}
	}
	return len;
}

void handle_env_variable(const char *str, int *i, char **result, int *j, int *len, t_shell *shell)
{
	char *var_name;
	char *env_value;
	int env_len;

	(*i)++;
	var_name = extract_var_name(str, i);
	env_value = get_env_value(var_name, shell);
	free(var_name);
	if (env_value)
	{
		env_len = ft_strlen(env_value);
		ft_strncpy(&(*result)[*j], env_value, env_len);
		*j += env_len;
		*len += env_len;
	}
}

char *ft_expander(char *str, t_shell *shell)
{
	int i;
	int j;
	int final_len;
	char *result;

	i = 0;
	j = 0;
	final_len = estimate_final_length(str, shell);
	result = malloc(final_len + 1);
	if (!result)
		return NULL;

	while (str[i])
	{
		if (str[i] == '$' && is_var_char(str[i + 1]))
			handle_env_variable(str, &i, &result, &j, &final_len, shell);
		else
			add_char_to_result(&result, &j, str[i++]);
	}
	result[j] = '\0';
	return result;
}