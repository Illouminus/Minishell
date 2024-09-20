/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/09/20 11:07:00 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_handle_redirection_token(t_token **current_token, t_parser_data *data)
{
	int result;

	result = 0;
	if (!(*current_token)->next_tok)
	{
		ft_putstr_fd("Syntax error: newline unexpected\n", STDOUT_FILENO);
		return (1);
	}
	else if (((*current_token)->tok_type == TOKEN_TYPE_REDIR_APPEND && !(*current_token)->next_tok->next_tok))
	{
		ft_putstr_fd("Syntax error: newline unexpected\n", STDOUT_FILENO);
		return (1);
	}
	else
	{
		result = ft_parser_handle_redirection(current_token, data->shell,
														  data->last_command);
		if (result == 0 && (*(data->last_command))->cmd_value == NULL)
			data->shell->expected_cmd = true;
		return (result);
	}
}

void ft_handle_argument_token(t_parser_data *data, char *cmd_value_clean)
{
	(*(data->last_command))->cmd_args[*(data->i)] = ft_expander(cmd_value_clean,
																					data->shell);
	(*(data->i))++;
}

int ft_process_token_parser(t_token **current_token, t_parser_data *data, char *cmd_value_clean)
{
	t_token_type t_type;

	t_type = (*current_token)->tok_type;

	if (t_type == TOKEN_TYPE_PIPE)
		return handle_pipe_token(current_token, data);
	if (data->shell->expected_cmd)
		return handle_expected_cmd(current_token, data, cmd_value_clean);
	if (t_type == TOKEN_TYPE_CMD)
		ft_handle_command_token(current_token, data, cmd_value_clean);
	else if (t_type == TOKEN_TYPE_REDIR_IN || t_type == TOKEN_TYPE_REDIR_OUT ||
				t_type == TOKEN_TYPE_REDIR_APPEND || t_type == TOKEN_TYPE_HEREDOC)
		return (ft_handle_redirection_token(current_token, data));
	else if (t_type == TOKEN_TYPE_ARG &&
				(*current_token)->prev_tok->tok_type != TOKEN_TYPE_REDIR_IN &&
				(*current_token)->prev_tok->tok_type != TOKEN_TYPE_REDIR_OUT &&
				!data->shell->expected_cmd)
		ft_handle_argument_token(data, cmd_value_clean);
	return (0);
}

int ft_parser_process_token(t_token **current_token, t_shell *shell,
									 t_command **last_command, int *i)
{
	char *cmd_value_clean;
	t_parser_data data;
	int result;

	data.shell = shell;
	data.last_command = last_command;
	data.i = i;
	cmd_value_clean = ft_expander((*current_token)->tok_value, shell);
	result = ft_handle_empty_command(cmd_value_clean, current_token);
	if (result == 2)
		return (0);
	else if (result == 1)
	{
		free(cmd_value_clean);
		return (1);
	}
	if (ft_process_token_parser(current_token, &data, cmd_value_clean) == 1)
	{
		free(cmd_value_clean);
		return (1);
	}
	free(cmd_value_clean);
	*current_token = (*current_token)->next_tok;
	return (0);
}

int parser(t_shell *shell)
{
	t_token *current_token;
	t_command *last_command;
	int i;

	shell->expected_cmd = false;
	last_command = NULL;
	current_token = shell->token_list;
	i = 0;
	if (ft_check_user_input(shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (current_token)
	{
		if (ft_parser_process_token(&current_token, shell, &last_command,
											 &i) == 1)
			return (EXIT_FAILURE);
	}
	if (last_command && last_command->cmd_args)
		last_command->cmd_args[i] = NULL;
	return (EXIT_SUCCESS);
}
