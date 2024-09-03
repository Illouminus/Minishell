/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:41:19 by ebaillot          #+#    #+#             */
/*   Updated: 2024/09/03 15:50:20 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_command *current, t_shell *shell)
{
	if (current->next_cmd)
	{
		if (pipe(current->shell->pipe_fds) == -1)
			handle_error("pipe", strerror(errno), 1, shell);
	}
	shell->last_process_id = fork();
	if (shell->last_process_id == -1)
		handle_error("fork", strerror(errno), 1, shell);
}

int	open_redirection(t_redir *redir, int *fd, t_shell *shell)
{
	int	flags;

	if (redir->redirection_type == REDIR_IN)
		flags = O_RDONLY;
	else if (redir->redirection_type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	if (flags == O_RDONLY)
		*fd = check_and_open_file(redir->filename, flags, 0, shell);
	else
		*fd = check_and_open_file(redir->filename, flags, 0644, shell);
	if (*fd == -1)
		return (-1);
	return (0);
}

t_error_info	init_error_info(const char *filepath, const char *error_message, int exit_code)
{
	t_error_info error_info;

	error_info.filepath = filepath;
	error_info.error_message = error_message;
	error_info.exit_code = exit_code;

	return error_info;
}


void	handle_redirection_error(t_error_info error_info, t_shell *shell,
		int fd)
{
	if (fd != -1)
		close(fd);
	fprintf(stderr, "minishell: %s: %s\n", error_info.filepath,
		error_info.error_message);
	shell->last_exit_status = error_info.exit_code;
	free_shell(shell);
	exit(error_info.exit_code);
}