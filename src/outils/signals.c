/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:43:31 by edouard           #+#    #+#             */
/*   Updated: 2024/09/04 11:03:47 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_vars(t_env **env_var_list)
{
	t_env	*env_temp;

	while (*env_var_list)
	{
		env_temp = *env_var_list;
		*env_var_list = (*env_var_list)->next_env;
		free(env_temp->env_var_name);
		free(env_temp->env_value);
		free(env_temp);
	}
	*env_var_list = NULL;
}

void	handle_exit(t_shell *shell)
{
	if (!shell->user_input)
	{
		if (isatty(STDIN_FILENO))
			printf(" exit\n");
		global_exit(shell);
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	global_exit(t_shell *shell)
{
	if (shell->env_var_list)
		free_env_vars(&shell->env_var_list);
	if (shell->user_input)
	{
		free(shell->user_input);
		shell->user_input = NULL;
	}
	free_shell(shell);
	clear_history();
	exit(shell->last_exit_status);
}
