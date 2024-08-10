/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:20 by edouard           #+#    #+#             */
/*   Updated: 2024/08/10 13:54:34 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_exit_error(const char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	shell->last_exit_status = 2;
	free_shell(shell);
}

static int get_exit_status(const char *arg, t_shell *shell)
{
	int stat = ft_atoi(arg);

	if (errno == ERANGE)
		handle_exit_error(arg, shell);

	if (stat > 255)
		return (stat % 256);
	else if (stat < 0)
		return ((stat % 256) + 256);

	return stat;
}

void ft_builtin_exit(t_command *commands, t_shell *shell)
{
	if (commands->cmd_args[0])
	{
		if (commands->cmd_args[1])
		{
			perror("too many arguments");
			shell->last_exit_status = 1;
			return;
		}
		shell->last_exit_status = get_exit_status(commands->cmd_args[0], shell);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_shell(shell);
	exit(shell->last_exit_status);
}