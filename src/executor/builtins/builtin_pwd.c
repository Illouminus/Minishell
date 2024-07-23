/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:24 by edouard           #+#    #+#             */
/*   Updated: 2024/07/23 12:26:04 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_current_directory(void)
{
	char *cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		print_error("pwd", strerror(errno));
	return cwd;
}

int ft_builtin_pwd(t_command *commands)
{
	if (commands->cmd_args[1] && commands->cmd_args[1][0] == '-')
	{
		print_error(commands->cmd_args[0], "invalid option");
		return 2;
	}

	char *cwd = get_current_directory();
	if (cwd == NULL)
		return 1;

	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	return 0;
}
