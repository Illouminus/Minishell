/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:02:55 by ebaillot          #+#    #+#             */
/*   Updated: 2024/09/27 14:50:47 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcat_local(char *dst, const char *src)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
}

void	ft_strcpy_local(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*create_env_var_string(t_env *env_var)
{
	char	*full_env_var;
	int		total_length;

	total_length = ft_strlen(env_var->env_var_name)
		+ ft_strlen(env_var->env_value) + 2;
	full_env_var = (char *)malloc(total_length);
	if (!full_env_var)
		return (NULL);
	ft_strcpy_local(full_env_var, env_var->env_var_name);
	ft_strcat_local(full_env_var, "=");
	ft_strcat_local(full_env_var, env_var->env_value);
	return (full_env_var);
}

char	**create_env_array(int count)
{
	char	**env_array;

	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	return (env_array);
}

char	**convert_env_list_to_array(t_env *env_list)
{
	int		count;
	int		i;
	char	**env_array;

	count = count_env_vars(env_list);
	env_array = create_env_array(count);
	if (!env_array)
		return (NULL);
	i = 0;
	while (env_list)
	{
		env_array[i] = create_env_var_string(env_list);
		if (!env_array[i])
		{
			while (i-- > 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		env_list = env_list->next_env;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
