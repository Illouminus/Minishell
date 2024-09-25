/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:19:29 by ahors             #+#    #+#             */
/*   Updated: 2024/09/25 16:18:33 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_in(t_token **current_token, t_shell *shell,
		t_command **last_command)
{
	char	*token_value;
	char	*file_name;

	token_value = (*current_token)->next_tok->tok_value;
	if (!token_value || (*current_token)->next_tok->tok_type == TOKEN_TYPE_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(token_value, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		shell->last_exit_status = 2;
		return (1);
	}
	file_name = ft_expander(token_value, shell);
	add_redirection(last_command, REDIR_IN, file_name);
	*current_token = (*current_token)->next_tok;
	free(file_name);
	return (0);
}

int	handle_heredoc(t_token **current_token, t_command *last_command)
{
	char	*file_name;

	*current_token = (*current_token)->next_tok->next_tok;
	if(!(*current_token))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (1);
	}
	file_name = ft_heredoc_handler((*current_token)->tok_value,
			last_command->shell);
	if (!file_name)
		return (1);
	add_redirection(&last_command, REDIR_IN, file_name);
	free(file_name);
	return (0);
}

void	handle_redir_out(t_token **current_token, t_shell *shell,
		t_command *last_command)
{
	char	*token_value;
	char	*file_name;

	token_value = (*current_token)->next_tok->tok_value;
	file_name = ft_expander(token_value, shell);
	add_redirection(&last_command, REDIR_OUT, file_name);
	free(file_name);
}

int	handle_redir_append(t_token **current_token, t_shell *shell,
		t_command *last_command)
{
	char	*token_value;
	char	*file_name;

	token_value = NULL;
	if ((*current_token)->next_tok)
		token_value = (*current_token)->next_tok->tok_value;
	if (!token_value || (*current_token)->next_tok->tok_type == TOKEN_TYPE_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(token_value, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		shell->last_exit_status = 2;
		return (1);
	}
	file_name = ft_expander(token_value, shell);
	add_redirection(&last_command, REDIR_APPEND, file_name);
	free(file_name);
	return (0);
}

int	ft_parser_handle_redirection(t_token **current_token, t_shell *shell,
		t_command **last_command)
{
	if ((*last_command) == NULL)
		*last_command = create_command_add_redirection(shell);
	if (shell->command_list == NULL)
		shell->command_list = *last_command;
	if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_IN)
	{
		if (handle_redir_in(current_token, shell, last_command) == 1)
			return (1);
	}
	else if ((*current_token)->tok_type == TOKEN_TYPE_HEREDOC)
	{
		if (handle_heredoc(current_token, (*last_command)) == 1)
			return (1);
	}
	else if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_OUT)
	{
		handle_redir_out(current_token, shell, (*last_command));
	}
	else if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_APPEND)
	{
		(*current_token) = (*current_token)->next_tok;
		if (handle_redir_append(current_token, shell, (*last_command)) == 1)
			return (1);
	}
	return (0);
}
