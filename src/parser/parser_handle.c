/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:15:37 by ahors             #+#    #+#             */
/*   Updated: 2024/09/20 11:07:43 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_parser_handle_command(t_token *current_token, char *cmd_value_clean,
										t_shell *shell, t_command **last_command)
{
	int cmd_nb_args;
	t_command *new_command;

	new_command = NULL;
	cmd_nb_args = ft_determine_nb_args(current_token);

	if ((*last_command) && !(*last_command)->cmd_value && shell->command_list && shell->expected_cmd)
	{
		(*last_command)->cmd_value = ft_strdup(cmd_value_clean);
		(*last_command)->is_builtin_cmd = ft_cmd_is_built_in((*last_command)->cmd_value);
		(*last_command)->cmd_args = malloc((cmd_nb_args + 1) * sizeof(char *));
	}
	else
	{
		new_command = ft_new_command_init(new_command, cmd_nb_args, cmd_value_clean,
													 shell);
		if (*last_command)
		{
			(*last_command)->next_cmd = new_command;
			new_command->prev_cmd = *last_command;
		}
		else
			shell->command_list = new_command;
		*last_command = new_command;
	}
}

int ft_parser_handle_empty_command(char *cmd_value_clean,
											  t_token **current_token)
{
	if (*cmd_value_clean == '\0' && (*current_token)->next_tok)
	{
		*current_token = (*current_token)->next_tok;
		(*current_token)->tok_type = TOKEN_TYPE_CMD;
		return (1);
	}
	return (0);
}

void ft_handle_command_token(t_token **current_token, t_parser_data *data,
									  char *cmd_value_clean)
{
	if (*(data->last_command) && (*(data->last_command))->cmd_args)
		(*(data->last_command))->cmd_args[*(data->i)] = NULL;
	ft_parser_handle_command(*current_token, cmd_value_clean, data->shell,
									 data->last_command);
	*(data->i) = 0;
}
