/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:03:53 by edouard           #+#    #+#             */
/*   Updated: 2024/09/04 15:32:07 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	estimate_final_length(const char *str, t_shell *shell)
{
	int		len;
	int		i;
	char	*var_name;
	char	*env_value;

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
			else
				len = 0;
			free(var_name);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	handle_env_variable(const char *str, int *i, t_expand_state *state,
		t_shell *shell)
{
	char	*var_name;
	char	*env_value;
	int		env_len;

	(*i)++;
	var_name = extract_var_name(str, i);
	env_value = get_env_value(var_name, shell);
	free(var_name);
	if (env_value)
	{
		env_len = ft_strlen(env_value);
		ft_strncpy(&(*state->result)[*state->j], env_value, env_len);
		*(state->j) += env_len;
		*(state->len) += env_len;
	}
	else
	{
		(*state->result)[*state->j] = '\0';
		*(state->j) += 1;
	}
}

void	handle_exit_status(char **result, int *j, t_shell *shell)
{
	char	*exit_status_str;
	int		exit_len;

	exit_status_str = ft_itoa(shell->last_exit_status);
	if (exit_status_str)
	{
		exit_len = ft_strlen(exit_status_str);
		ft_strncpy(&(*result)[*j], exit_status_str, exit_len);
		*j += exit_len;
		free(exit_status_str);
	}
}

void	process_characters(char *str, t_expand_state *state, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_var_char(str[i + 1]))
		{
			handle_env_variable(str, &i, state, shell);
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			i += 2;
			handle_exit_status(state->result, state->j, shell);
		}
		else
		{
			add_char_to_result(state->result, state->j, str[i++]);
		}
	}
}

char	*ft_expander(char *str, t_shell *shell, int inside_single_quote)
{
	int				i;
	int				j;
	int				final_len;
	char			*result;
	t_expand_state	state;

	i = 0;
	j = 0;
	if (inside_single_quote)
		return (ft_strdup(str));
	final_len = estimate_final_length(str, shell);
	result = malloc(final_len + 1);
	if (!result)
		return (NULL);
	state.result = &result;
	state.j = &j;
	state.len = &final_len;
	process_characters(str, &state, shell);
	if(final_len == 0)
		result[0] = '\0';
	else
		result[j] = '\0';
	return (result);
}
