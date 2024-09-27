/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:43:31 by edouard           #+#    #+#             */
/*   Updated: 2024/09/27 14:41:46 by ebaillot         ###   ########.fr       */
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
		g_exit_code = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signal_handlers(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
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
