/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:19:29 by ahors             #+#    #+#             */
/*   Updated: 2024/09/27 15:49:08 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_in(t_token **current_token, t_parser_data *data,
		t_command **last_command)
{
	char	*token_value;
	char	*file_name;

	if (!(*current_token)->next_tok)
		return (handle_error_parsing("newline", data, 2, 1));
	token_value = (*current_token)->next_tok->tok_value;
	if ((*current_token)->next_tok->tok_type == TOKEN_TYPE_PIPE)
		return (handle_error_parsing(token_value, data, 2, 1));
	file_name = ft_expander(token_value, data->shell);
	add_redirection(last_command, REDIR_IN, file_name);
	(*current_token) = (*current_token)->next_tok;
	free(file_name);
	return (0);
}

int	handle_heredoc(t_token **current_token, t_parser_data *data,
		t_command *last_command)
{
	char	*file_name;

	if (!(*current_token)->next_tok || !(*current_token)->next_tok->next_tok)
		return (handle_error_parsing("newline", data, 2, 1));
	*current_token = (*current_token)->next_tok->next_tok;
	file_name = ft_heredoc_handler((*current_token)->tok_value,
			last_command->shell);
	if (!file_name)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	add_redirection(&last_command, REDIR_IN, file_name);
	free(file_name);
	return (0);
}

int	handle_redir_out(t_token **current_token, t_parser_data *data,
		t_command *last_command)
{
	char	*token_value;
	char	*file_name;

	if (!(*current_token)->next_tok)
		return (handle_error_parsing("newline", data, 2, 1));
	token_value = (*current_token)->next_tok->tok_value;
	file_name = ft_expander(token_value, data->shell);
	add_redirection(&last_command, REDIR_OUT, file_name);
	(*current_token) = (*current_token)->next_tok;
	free(file_name);
	return (0);
}

int	handle_redir_append(t_token **current_token, t_parser_data *data,
		t_command *last_command)
{
	char	*token_value;
	char	*file_name;

	if (!(*current_token)->next_tok)
		return (handle_error_parsing("newline", data, 2, 1));
	if (!(*current_token)->next_tok->next_tok)
		return (handle_error_parsing("newline", data, 2, 1));
	token_value = (*current_token)->next_tok->next_tok->tok_value;
	if ((*current_token)->next_tok->tok_type == TOKEN_TYPE_PIPE)
		return (handle_error_parsing(token_value, data, 2, 1));
	file_name = ft_expander(token_value, data->shell);
	add_redirection(&last_command, REDIR_APPEND, file_name);
	(*current_token) = (*current_token)->next_tok;
	free(file_name);
	return (0);
}

int	ft_parser_handle_redirection(t_token **current_token, t_parser_data *data,
		t_command **last_command)
{
	if ((*last_command) == NULL)
		*last_command = create_command_add_redirection(data->shell);
	if (data->shell->command_list == NULL)
		data->shell->command_list = *last_command;
	if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_IN)
		return (handle_redir_in(current_token, data, last_command));
	else if ((*current_token)->tok_type == TOKEN_TYPE_HEREDOC)
		return (handle_heredoc(current_token, data, (*last_command)));
	else if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_OUT)
		return (handle_redir_out(current_token, data, (*last_command)));
	else if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_APPEND)
		return (handle_redir_append(current_token, data, (*last_command)));
	return (0);
}
