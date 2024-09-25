/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:03:53 by edouard           #+#    #+#             */
/*   Updated: 2024/09/25 14:28:06 by ebaillot         ###   ########.fr       */
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
	char *var_name = NULL;
	char *expanded_value;

	start = *i + 1;
	while (ft_isalnum(str[start]) || str[start] == '_')
		start++;

	if (start == *i + 1)
	{
		*i += 1;
		return ft_strdup("$");
	}
	var_name = ft_substr(str, *i + 1, start - (*i + 1));
	*i = start;
	expanded_value = get_env_value(var_name, shell);
	free(var_name);

	if (!expanded_value)
		return ft_strdup("");
	return expanded_value;
}

void get_exit_code(char *result, int *j, t_shell *shell, int *i)
{
	char *exit_code_str;

	*i += 2;
	exit_code_str = ft_itoa(shell->last_exit_status);
	ft_strncpy(&result[*j], exit_code_str, ft_strlen(exit_code_str));
	*j += ft_strlen(exit_code_str);
	free(exit_code_str);
}

void handle_variable_expansion(const char *str, int *i, t_expand_state *state, t_shell *shell)
{
	char *expanded_var = expand_variable(str, i, shell);
	if (!expanded_var)
		expanded_var = ft_strdup("");

	int var_len = strlen(expanded_var);
	ft_strncpy(&state->result[state->j], expanded_var, var_len);
	state->j += var_len;
	free(expanded_var);
}

void process_characters(char *str, t_expand_state *state, t_shell *shell)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '?' && !state->inside_single_quote)
			get_exit_code(state->result, &state->j, shell, &i);
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
		else if (str[i] == '$' && !state->inside_single_quote)
			handle_variable_expansion(str, &i, state, shell);
		else
			state->result[state->j++] = str[i++];
	}
	state->result[state->j] = '\0';
}

char *ft_expander(char *str, t_shell *shell)
{
	char *result;
	t_expand_state *state;
	result = malloc(10000);

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
