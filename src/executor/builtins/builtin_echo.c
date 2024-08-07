/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:15 by edouard           #+#    #+#             */
/*   Updated: 2024/08/07 11:54:31 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_builtin_echo(t_command *cmd)
{
	int i;
	bool newline;
	i = 0;
	newline = true;

	if (cmd->cmd_value && !ft_strcmp(cmd->cmd_args[0], "-n"))
	{
		newline = false;
		i++;
	}
	while (cmd->cmd_args[i + 1])
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