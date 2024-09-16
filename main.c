/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:56:44 by edouard           #+#    #+#             */
/*   Updated: 2024/09/16 13:11:13 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

t_command *create_command_add_redirection() {
    t_command *cmd;
	cmd  = malloc(sizeof(t_command));
    if (!cmd) 
      return NULL;
    cmd->cmd_args = NULL;
    cmd->redirections = NULL;
    cmd->last_redirection = NULL;
    cmd->next_cmd = NULL;
    return cmd;
}

int	minishell(t_shell *shell, char **env)
{
	if (init_shell(shell, env) == 1)
		return (1);
	while (1)
	{
		setup_signal_handlers();
		shell->user_input = readline("minishell >>  ");
		if (g_exit_code == 130)
		{
			shell->last_exit_status = 130;
			g_exit_code = 0;
		}
		handle_exit(shell);
		if (lexer(shell) == EXIT_SUCCESS && parser(shell) == EXIT_SUCCESS)
		{
			g_exit_code = ft_executor(shell);
			shell->last_exit_status = g_exit_code;
		}
		else
		{
			g_exit_code = 1;
			shell->last_exit_status = g_exit_code;
		}
		free_shell(shell);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	minishell(&shell, env);
	global_exit(&shell);
	return (0);
}
