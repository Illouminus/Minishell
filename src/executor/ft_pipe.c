/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:41:19 by ebaillot          #+#    #+#             */
/*   Updated: 2024/09/18 12:25:33 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pipe(t_command *current, t_shell *shell)
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

int open_redirection(t_redir *redir, int *fd, t_shell *shell)
{
	int flags;

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

t_error_info init_error_info(char *filepath, char *error_message,
									  int exit_code)
{
	t_error_info error_info;

	error_info.filepath = filepath;
	error_info.error_message = error_message;
	error_info.exit_code = exit_code;
	return (error_info);
}

void handle_redirection_error(t_error_info error_info, t_shell *shell,
										int fd)
{
	if (fd != -1)
		close(fd);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error_info.filepath, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_info.error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->last_exit_status = error_info.exit_code;
	free_shell(shell);
	exit(error_info.exit_code);
}

int count_env_vars(t_env *env_list)
{
	int count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next_env;
	}
	return (count);
}
