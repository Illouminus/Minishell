/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:21:43 by edouard           #+#    #+#             */
/*   Updated: 2024/08/07 11:33:08 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_input_redirection(const char *input_file)
{
	int input_fd;

	if (input_file)
	{
		input_fd = open(input_file, O_RDONLY);
		if (input_fd == -1)
		{
			perror("failed to open input file");
			return; // TODO: handle error properly
		}
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for input");
			close(input_fd);
			return; // TODO: handle error properly
		}
		close(input_fd);
	}
}

static void handle_output_redirection(const char *output_file)
{
	int output_fd;

	if (output_file)
	{
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
		{
			perror("failed to open output file");
			return; // TODO: handle error properly
		}
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for output");
			close(output_fd);
			return; // TODO: handle error properly
		}
		close(output_fd);
	}
}

static void handle_pipe_redirection(t_command *current)
{
	if (current->next_cmd)
	{
		if (dup2(current->pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for pipe_fds[1]");
			close(current->pipe_fds[0]);
			close(current->pipe_fds[1]);
			return; // TODO: handle error properly
		}
		close(current->pipe_fds[0]);
		close(current->pipe_fds[1]);
	}
}

static void handle_prev_fd_redirection(int prev_fd)
{
	if (prev_fd != 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for pipe input");
			close(prev_fd);
			return; // TODO: handle error properly
		}
		close(prev_fd);
	}
}

void handle_redirections(t_command *current, int prev_fd)
{
	handle_input_redirection(current->input_file);
	handle_output_redirection(current->output_file);
	handle_pipe_redirection(current);
	handle_prev_fd_redirection(prev_fd);
}