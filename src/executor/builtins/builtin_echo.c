/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:15 by edouard           #+#    #+#             */
/*   Updated: 2024/09/03 15:59:20 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_echo(t_command *cmd)
{
	int		i;
	bool	newline;

	i = 0;
	newline = true;
	if ((cmd->cmd_value && !cmd->cmd_args[0]))
	{
		newline = false;
		i++;
	}
	if (cmd->cmd_args[0] && ft_strcmp(cmd->cmd_args[0], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		ft_putstr_fd(cmd->cmd_args[i], STDOUT_FILENO);
		if (cmd->cmd_args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
