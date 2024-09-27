/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_outils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:36:00 by edouard           #+#    #+#             */
/*   Updated: 2024/09/27 18:52:07 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file_exists_and_stat(char *filepath, t_shell *shell,
		struct stat *file_stat)
{
	t_error_info	error_info;

	if (access(filepath, F_OK) == 0)
	{
		if (stat(filepath, file_stat) == -1)
		{
			error_info = init_error_info(filepath, strerror(errno), 1);
			handle_redirection_error(error_info, shell, -1);
			return (-1);
		}
		return (1);
	}
	return (0);
}

static int	check_if_directory(char *filepath, const struct stat *file_stat,
		t_shell *shell)
{
	t_error_info	error_info;

	if (S_ISDIR(file_stat->st_mode))
	{
		error_info = init_error_info(filepath, "Is a directory", 126);
		handle_redirection_error(error_info, shell, -1);
		return (-1);
	}
	return (0);
}

static int	check_write_permission(char *filepath, int flags, t_shell *shell)
{
	t_error_info	error_info;

	if ((flags & O_WRONLY) && access(filepath, W_OK) == -1)
	{
		error_info = init_error_info(filepath, strerror(errno), 1);
		handle_redirection_error(error_info, shell, -1);
		return (-1);
	}
	return (0);
}

static int	open_file_with_checks(char *filepath, int flags, mode_t mode)
{
	int	fd;

	fd = open(filepath, flags, mode);
	if (fd == -1)
		perror("open error");
	return (fd);
}


int	check_and_open_file(char *filepath, int flags, mode_t mode, t_shell *shell)
{
	struct stat		file_stat;
	int				file_exists;
	t_error_info	error_info;

	file_exists = check_file_exists_and_stat(filepath, shell, &file_stat);
	if (file_exists == -1)
		return (-1);
	if (file_exists == 1)
	{
		if (check_if_directory(filepath, &file_stat, shell) == -1)
			return (-1);
		if (check_write_permission(filepath, flags, shell) == -1)
			return (-1);
	}
	else if (!(flags & O_WRONLY))
	{
		error_info = init_error_info(filepath, "No such file or directory", 1);
		handle_redirection_error(error_info, shell, -1);
		return (-1);
	}
	return (open_file_with_checks(filepath, flags, mode));
}
