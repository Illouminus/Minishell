/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:24 by edouard           #+#    #+#             */
/*   Updated: 2024/08/09 11:48:56 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_current_directory(void)
{
	char *cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd("pwd: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return cwd;
}

int ft_builtin_pwd(t_command *commands)
{
	if (commands->cmd_args[0] != NULL)
	{
		// ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		//  Вы можете вернуть код ошибки 1, если хотите строгую проверку.
		//  Но bash возвращает 0 даже при наличии дополнительных аргументов.
		//  return 1;
	}

	char *cwd = get_current_directory();
	if (cwd == NULL)
		return 1;

	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	return 0;
}
