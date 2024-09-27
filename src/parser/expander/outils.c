/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:39:36 by edouard           #+#    #+#             */
/*   Updated: 2024/09/27 15:48:53 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

int	ft_check_user_input(t_shell *shell)
{
	if (!shell->user_input || ft_strcmp(shell->user_input, "/0") == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_handle_empty_command(char *cmd_value_clean, t_token **current_token)
{
	if (ft_parser_handle_empty_command(cmd_value_clean, current_token) == 1)
	{
		free(cmd_value_clean);
		return (2);
	}
	return (0);
}

t_expand_state	*init_expand_state(char *result)
{
	t_expand_state	*state;

	state = malloc(sizeof(t_expand_state));
	if (!state)
		return (NULL);
	state->result = result;
	state->j = 0;
	state->inside_single_quote = 0;
	state->inside_double_quote = 0;
	return (state);
}

int	handle_error_parsing(char *unexpected_token, t_parser_data *data,
		int exit_status, int return_status)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(unexpected_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	data->shell->last_exit_status = exit_status;
	return (return_status);
}
