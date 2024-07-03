/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:56:44 by edouard           #+#    #+#             */
/*   Updated: 2024/07/03 18:14:49 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

int minishell(char **env)
{
	t_shell shell;

	if (init_shell(&shell, env) == 1)
		return (1);
	while (1)
	{
		shell.user_input = readline("minishell >>  ");
		if (g_exit_code == 130)
		{
			shell.last_exit_status = 130;
			g_exit_code = 0;
		}

		handle_exit(&shell);
		// Check if the user input is empty
		// Check if the user input is a comment
		// Check if the user input is a builtin command
		// Check if the user input is a binary
		// Check if the user input is a path
		// Check if the user input is a variable assignment
		// Check if the user input is a redirection
		// Check if the user input is a pipe
		// Check if the user input is a heredoc
		// Check if the user input is a separator
		// Check if the user input is a list
		// Check if the user input is a command
		// Check if the user input is a syntax error
		// Check if the user input is a permission error

		add_history(shell.user_input);
	}
	return 0;
}

int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;

	return minishell(env);
}