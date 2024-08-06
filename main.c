/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:56:44 by edouard           #+#    #+#             */
/*   Updated: 2024/08/06 16:25:49 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ncurses.h>

int g_exit_code;

int minishell(char **env)
{
	t_shell shell;
	t_token *temp; 
	t_command *temp_command; 

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
		{
			g_exit_code = executor(&shell);
			// Lines to free token_list between each command --> Put in a separate function
			while (shell.token_list != NULL) 
			{
				temp = shell.token_list;
				shell.token_list = shell.token_list->next_tok;
				free(temp->tok_value); 
				free(temp);
			}
			while (shell.command_list != NULL)
			{
				temp_command = shell.command_list;
				shell.command_list = shell.command_list->next_cmd;
				free(temp_command->cmd_value);
				printf("Command Value was freed\n"); 
				ft_free_cmd_args(temp_command->cmd_args); 
				printf("Command Args was freed\n"); 
				free(temp_command);
				printf("Command was freed\n"); 
			}	
		}
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