/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:15:37 by ahors             #+#    #+#             */
/*   Updated: 2024/08/30 11:26:06 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser_handle_redirection(t_token **current_token, t_shell *shell,
		t_command *last_command, int *inside_single_quote)
{
	char	*file_name;

	if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_IN)
	{
		file_name = ft_expander(ft_clean_token_value((*current_token)->next_tok->tok_value,
					inside_single_quote), shell, *inside_single_quote);
		add_redirection(last_command, REDIR_IN, file_name);
	}
	else if ((*current_token)->tok_type == TOKEN_TYPE_HEREDOC)
	{
		*current_token = (*current_token)->next_tok->next_tok;
		file_name = ft_heredoc_handler((*current_token)->tok_value);
		add_redirection(last_command, REDIR_IN, file_name);
	}
	else if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_OUT)
	{
		file_name = ft_expander(ft_clean_token_value((*current_token)->next_tok->tok_value,
					inside_single_quote), shell, *inside_single_quote);
		add_redirection(last_command, REDIR_OUT, file_name);
	}
	else if ((*current_token)->tok_type == TOKEN_TYPE_REDIR_APPEND)
	{
		*current_token = (*current_token)->next_tok;
		file_name = ft_expander(ft_clean_token_value((*current_token)->next_tok->tok_value,
					inside_single_quote), shell, *inside_single_quote);
		add_redirection(last_command, REDIR_APPEND, file_name);
	}
}

void	ft_parser_handle_command(t_token *current_token, char *cmd_value_clean,
		t_shell *shell, t_command **last_command)
{
	int			cmd_nb_args;
	t_command	*new_command;

	new_command = NULL;
	cmd_nb_args = ft_determine_nb_args(current_token);
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

int	ft_parser_handle_empty_command(char *cmd_value_clean,
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

char	*ft_handle_token_expansion(t_token *current_token, t_shell *shell,
		int *inside_single_quote)
{
	*inside_single_quote = 0;
	return (ft_expander(ft_clean_token_value(current_token->tok_value,
				inside_single_quote), shell, *inside_single_quote));
}