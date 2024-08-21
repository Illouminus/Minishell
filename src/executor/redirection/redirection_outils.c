/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_outils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:36:00 by edouard           #+#    #+#             */
/*   Updated: 2024/08/21 16:42:17 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirection_error(const char *filepath, const char *error_message, int exit_code, t_shell *shell, int fd)
{
	if (fd != -1)
		close(fd);
	fprintf(stderr, "minishell: %s: %s\n", filepath, error_message);
	shell->last_exit_status = exit_code;
	free_shell(shell);
	exit(exit_code);
}

static int check_file_exists_and_stat(const char *filepath, t_shell *shell, struct stat *file_stat)
{
	if (access(filepath, F_OK) == 0)
	{
		if (stat(filepath, file_stat) == -1)
		{
			handle_redirection_error(filepath, strerror(errno), 1, shell, -1);
			return -1;
		}
	}
	else
	{
		return 0;
	}
	return 1;
}

static int check_if_directory(const char *filepath, const struct stat *file_stat, t_shell *shell)
{
	if (S_ISDIR(file_stat->st_mode))
	{
		handle_redirection_error(filepath, "Is a directory", 126, shell, -1);
		return -1;
	}
	return 0;
}

static int check_write_permission(const char *filepath, int flags, t_shell *shell)
{
	if ((flags & O_WRONLY) && access(filepath, W_OK) == -1)
	{
		handle_redirection_error(filepath, strerror(errno), 1, shell, -1);
		return -1;
	}
	return 0;
}

int check_and_open_file(const char *filepath, int flags, mode_t mode, t_shell *shell)
{
	int fd;
	struct stat file_stat;

	int file_exists = check_file_exists_and_stat(filepath, shell, &file_stat);
	if (file_exists == -1)
		return -1;
	if (file_exists == 1)
	{
		if (check_if_directory(filepath, &file_stat, shell) == -1)
			return -1;
		if (check_write_permission(filepath, flags, shell) == -1)
			return -1;
	}
	else if (!(flags & O_WRONLY))
	{
		handle_redirection_error(filepath, "No such file or directory", 1, shell, -1);
		return -1;
	}
	fd = open(filepath, flags, mode);
	if (fd == -1)
	{
		handle_redirection_error(filepath, strerror(errno), 1, shell, fd);
		return -1;
	}
	return fd;
}