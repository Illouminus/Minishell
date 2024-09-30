/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:55:08 by edouard           #+#    #+#             */
/*   Updated: 2024/09/30 10:47:15 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin_with_redirections(t_command *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	if (cmd->redirections == NULL)
	{
		ft_exec_builtins(cmd, shell, true);
		return ;
	}
	if (save_standard_fds(&saved_stdin, &saved_stdout) != 0)
		return ;
	if (validate_and_open_redirections(cmd, shell) == -1)
	{
		restore_standard_fds(saved_stdin, saved_stdout);
		return ;
	}
	ft_exec_builtins(cmd, shell, true);
	if (restore_standard_fds(saved_stdin, saved_stdout) != 0)
		return ;
}
