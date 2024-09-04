/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/09/04 12:05:19 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_handle_redirection_token(t_token **current_token,
		t_parser_data *data)
{
	ft_parser_handle_redirection(current_token, data->shell,
		*(data->last_command), &(data->inside_single_quote));
}

void	ft_handle_argument_token(t_parser_data *data, char *cmd_value_clean)
{
	(*(data->last_command))->cmd_args[*(data->i)] = ft_expander(cmd_value_clean,
			data->shell, data->inside_single_quote);
	(*(data->i))++;
}

void	ft_process_token(t_token **current_token, t_parser_data *data,
		char *cmd_value_clean)
{
	t_token_type	t_type;

	t_type = (*current_token)->tok_type;
	if (t_type == TOKEN_TYPE_CMD)
		ft_handle_command_token(current_token, data, cmd_value_clean);
	else if (t_type == TOKEN_TYPE_REDIR_IN || t_type == TOKEN_TYPE_REDIR_OUT
		|| t_type == TOKEN_TYPE_REDIR_APPEND || t_type == TOKEN_TYPE_HEREDOC)
		ft_handle_redirection_token(current_token, data);
	else if (t_type == TOKEN_TYPE_ARG
		&& (*current_token)->prev_tok->tok_type != TOKEN_TYPE_REDIR_IN
		&& (*current_token)->prev_tok->tok_type != TOKEN_TYPE_REDIR_OUT)
		ft_handle_argument_token(data, cmd_value_clean);
}

void	ft_parser_process_token(t_token **current_token, t_shell *shell,
		t_command **last_command, int *i)
{
	char			*cmd_value_clean;
	t_parser_data	data;

	data.shell = shell;
	data.last_command = last_command;
	data.i = i;
	cmd_value_clean = ft_expander_cleaned_token_value(*current_token, shell,
			&(data.inside_single_quote));
	if (ft_handle_empty_command(cmd_value_clean, current_token))
		return ;
	ft_process_token(current_token, &data, cmd_value_clean);
	free(cmd_value_clean);
	*current_token = (*current_token)->next_tok;
}

int	parser(t_shell *shell)
{
	t_token		*current_token;
	t_command	*last_command;
	int			i;

	last_command = NULL;
	current_token = shell->token_list;
	if (ft_check_user_input(shell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (current_token)
		ft_parser_process_token(&current_token, shell, &last_command, &i);
	if (last_command && last_command->cmd_args)
		last_command->cmd_args[i] = NULL;
	return (EXIT_SUCCESS);
}
