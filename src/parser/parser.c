/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/09/04 11:27:10 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_user_input(t_shell *shell)
{
	if (!shell->user_input || ft_strcmp(shell->user_input, "/0") == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_parser_process_token(t_token **current_token, t_shell *shell,
		t_command **last_command, int *i)
{
	int				inside_single_quote;
	char			*cmd_value_clean;
	t_token_type	t_type;

	t_type = (*current_token)->tok_type;
	cmd_value_clean = ft_expander_cleaned_token_value(*current_token, shell,
			&inside_single_quote);
	if (ft_parser_handle_empty_command(cmd_value_clean, current_token))
	{
		free(cmd_value_clean);
		return ;
	}
	if (t_type == TOKEN_TYPE_CMD)
	{
		if (*last_command && (*last_command)->cmd_args)
			(*last_command)->cmd_args[*i] = NULL;
		ft_parser_handle_command(*current_token, cmd_value_clean, shell,
			last_command);
		*i = 0;
	}
	else if (t_type == TOKEN_TYPE_REDIR_IN || t_type == TOKEN_TYPE_REDIR_OUT
		|| t_type == TOKEN_TYPE_REDIR_APPEND || t_type == TOKEN_TYPE_HEREDOC)
		ft_parser_handle_redirection(current_token, shell, *last_command,
			&inside_single_quote);
	else if (t_type == TOKEN_TYPE_ARG
		&& ((*current_token)->prev_tok->tok_type != TOKEN_TYPE_REDIR_IN
			&& (*current_token)->prev_tok->tok_type != TOKEN_TYPE_REDIR_OUT))
	{
		(*last_command)->cmd_args[*i] = ft_expander(cmd_value_clean, shell,
				inside_single_quote);
		(*i)++;
	}
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
