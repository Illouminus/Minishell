/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:56:44 by edouard           #+#    #+#             */
/*   Updated: 2024/07/16 16:33:26 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ncurses.h>

int g_exit_code;



int minishell(char **env)
{
	t_shell shell;

	if (init_shell(&shell, env) == 1)
		return (1);
	setup_signal_handlers();
	while (1)
	{
		shell.user_input = readline("minishell >>  ");
		if (g_exit_code == 130)
		{
			shell.last_exit_status = 130;
			g_exit_code = 0;
		}
		handle_exit(&shell);

		if (lexer(&shell) == EXIT_SUCCESS && parser(&shell) == EXIT_SUCCESS)
			g_exit_code = executor(&shell);
			
		else
		{
			g_exit_code = 1;
			printf("Parser or lexer presented an issue\n");
		}
		// TODO free_shell(shell) function is not implemented
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;

	return minishell(env);
}