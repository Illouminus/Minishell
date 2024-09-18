/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:11:50 by edouard           #+#    #+#             */
/*   Updated: 2024/09/18 13:17:04 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *create_command_add_redirection(t_shell *shell)
{
	t_command *cmd;
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;
	cmd->cmd_value = NULL;
	cmd->cmd_args = NULL;
	cmd->redirections = NULL;
	cmd->last_redirection = NULL;
	cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	cmd->is_builtin_cmd = false;
	cmd->shell = shell;
	return cmd;
}

int handle_pipe_token(t_token **current_token, t_parser_data *data)
{
	t_command *new_command = create_command_add_redirection(data->shell);
	if (!new_command)
	{
		ft_putstr_fd("Error: failed to create new command\n", STDERR_FILENO);
		return (1);
	}
	if (*data->last_command)
	{
		(*data->last_command)->next_cmd = new_command;
		new_command->prev_cmd = *data->last_command;
	}
	else
	{
		data->shell->command_list = new_command;
	}
	*data->last_command = new_command;
	data->shell->expected_cmd = true;
	return (0);
}

int handle_expected_cmd(t_token **current_token, t_parser_data *data, char *cmd_value_clean)
{
	t_token_type t_type = (*current_token)->tok_type;

	if (t_type == TOKEN_TYPE_REDIR_IN || t_type == TOKEN_TYPE_REDIR_OUT ||
		 t_type == TOKEN_TYPE_REDIR_APPEND || t_type == TOKEN_TYPE_HEREDOC)
	{
		if (ft_handle_redirection_token(current_token, data) == 1)
			return (1);
		return (0);
	}
	else if (t_type == TOKEN_TYPE_CMD || t_type == TOKEN_TYPE_ARG)
	{
		ft_handle_command_token(current_token, data, cmd_value_clean);
		(*current_token)->tok_type = TOKEN_TYPE_CMD;
		data->shell->expected_cmd = false;
		return (0);
	}
	else
	{
		ft_putstr_fd("Syntax error: unexpected token\n", STDERR_FILENO);
		return (1);
	}
}
