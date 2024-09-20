/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:03:53 by edouard           #+#    #+#             */
/*   Updated: 2024/09/20 11:41:08 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand_state *init_expand_state(char *result)
{
	t_expand_state *state;

	state = malloc(sizeof(t_expand_state));
	if (!state)
		return (NULL);

	state->result = result;
	state->j = 0;
	state->inside_single_quote = 0;
	state->inside_double_quote = 0;

	return (state);
}

char *expand_variable(const char *str, int *i, t_shell *shell)
{
	int start;
	char *var_name;
	char *expanded_value;

	start = *i + 1;
	while (ft_isalnum(str[start]) || str[start] == '_')
		start++;

	var_name = ft_substr(str, *i + 1, start - (*i + 1));
	*i = start;

	expanded_value = get_env_value(var_name, shell);
	free(var_name);

	if (!expanded_value)
		return "";
	return expanded_value;
}

void process_characters(char *str, t_expand_state *state, t_shell *shell)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !state->inside_single_quote)
		{
			char *expanded_var = expand_variable(str, &i, shell);
			int var_len = ft_strlen(expanded_var);
			ft_strncpy(&state->result[state->j], expanded_var, var_len);
			state->j += var_len;
		}
		else if (str[i] == '\'' && !state->inside_double_quote)
		{
			state->inside_single_quote = !state->inside_single_quote;
			i++;
		}
		else if (str[i] == '"' && !state->inside_single_quote)
		{
			state->inside_double_quote = !state->inside_double_quote;
			i++;
		}
		else
			state->result[state->j++] = str[i++];
	}
	state->result[state->j] = '\0';
}

char *ft_expander(char *str, t_shell *shell)
{
	int final_len;
	char *result;
	t_expand_state *state;

	final_len = ft_strlen(str);
	result = malloc(final_len + 1);

	if (!result)
		return NULL;
	state = init_expand_state(result);

	if (!state)
	{
		free(result);
		return NULL;
	}
	process_characters(str, state, shell);
	free(state);
	return result;
}
