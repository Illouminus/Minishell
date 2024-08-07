/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:43 by edouard           #+#    #+#             */
/*   Updated: 2024/08/06 17:19:50 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirections(t_command *current, int prev_fd)
{
	int input_fd;
	int output_fd;

	if (current->input_file)
	{
		input_fd = open(current->input_file, O_RDONLY);
		if (input_fd == -1)
			perror("failed to open input file"); // TODO: handle error
		if (dup2(input_fd, STDIN_FILENO) == -1)
			perror("dup2 failed for input");
		close(input_fd);
	}
	if (current->output_file)
	{
		output_fd = open(current->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
			perror("failed to open output file");
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			perror("dup2 failed for output");
		close(output_fd);
	}
	if (current->next_cmd)
	{
		if (dup2(current->pipe_fds[1], STDOUT_FILENO) == -1)
			perror("dup2 failed for pipe_fds[1]");
		close(current->pipe_fds[0]);
		close(current->pipe_fds[1]);
	}
	if (prev_fd != 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			perror("dup2 failed for pipe input");
		close(prev_fd);
	}
}
