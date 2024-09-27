/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:24 by edouard           #+#    #+#             */
/*   Updated: 2024/09/27 14:49:18 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_directory(t_shell *shell)
{
	char	*pwd;

	pwd = ft_getenv(shell->env_var_list, "PWD");
	if (!pwd)
		handle_error_non_critical("pwd", "PWD not set", 1, shell);
	return (pwd);
}

int	ft_builtin_pwd(t_command *commands)
{
	char	*pwd;
	t_shell	*shell;

	shell = commands->shell;
	pwd = get_current_directory(shell);
	if (pwd == NULL)
		return (1);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
	return (0);
}
