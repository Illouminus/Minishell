/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:15:37 by ahors             #+#    #+#             */
/*   Updated: 2024/09/02 11:28:29 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_expander_cleaned_token_value(t_token *current_token, t_shell *shell,
		int *inside_single_quote)
{
	*inside_single_quote = 0;
	char *cleaned_token = ft_clean_token_value(current_token->tok_value,
				inside_single_quote);
	char *expanded_token = ft_expander(cleaned_token, shell, *inside_single_quote);
	free(cleaned_token); 
	return expanded_token;
}

