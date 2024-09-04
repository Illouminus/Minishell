/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_outils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:35:44 by ebaillot          #+#    #+#             */
/*   Updated: 2024/09/04 10:41:08 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cd_error(t_error_info error_info, t_shell *shell, char *s1, char *s2)
{
	handle_error_non_critical(error_info.filepath, error_info.error_message,
		error_info.exit_code, shell);
	free(s1);
	free(s2);
	return (1);
}

void	ft_update_pwd(t_shell *shell, char *command)
{
	char	cwd[4096];
	char	*old_dir;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		handle_error_non_critical(command, strerror(errno), 1, shell);
		return ;
	}
	old_dir = ft_getenv(shell->env_var_list, "PWD");
	if (!old_dir)
		return ;
	ft_setenv(&shell->env_var_list, "OLDPWD", old_dir);
	free(old_dir);
	ft_setenv(&shell->env_var_list, "PWD", cwd);
}

int	ft_fd_minus(t_shell *shell, int option)
{
	char	*curr_dir;
	char	*old_dir;

	curr_dir = ft_getenv(shell->env_var_list, "OLDPWD");
	old_dir = ft_getenv(shell->env_var_list, "PWD");
	if (!curr_dir)
		return (handle_cd_error((t_error_info){"cd", "OLDPWD not set", 1},
			shell, curr_dir, old_dir));
	if (!old_dir)
		return (handle_cd_error((t_error_info){"cd", "PWD not set", 1}, shell,
			curr_dir, old_dir));
	if (chdir(curr_dir) == -1)
		return (handle_cd_error((t_error_info){"cd", strerror(errno), 1}, shell,
			curr_dir, old_dir));
	if (option == 1)
	{
		handle_cd_error((t_error_info){"cd", "too many arguments", 1}, shell,
			curr_dir, old_dir);
	}
	ft_setenv(&shell->env_var_list, "OLDPWD", old_dir);
	ft_setenv(&shell->env_var_list, "PWD", curr_dir);
	free(curr_dir);
	free(old_dir);
	return (0);
}
