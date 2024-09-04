/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:39:36 by edouard           #+#    #+#             */
/*   Updated: 2024/09/04 13:31:03 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_char_to_result(char **result, int *j, char c)
{
	(*result)[(*j)++] = c;
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*extract_var_name(const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && is_var_char(str[*i]))
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
	if (ft_parser_handle_empty_command(cmd_value_clean, current_token))
	{
		free(cmd_value_clean);
		return (1);
	}
	return (0);
}
