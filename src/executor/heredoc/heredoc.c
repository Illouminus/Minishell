/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:38:46 by edouard           #+#    #+#             */
/*   Updated: 2024/08/20 14:41:39 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEREDOC_BUFFER_SIZE 1024
#define HEREDOC_TEMPFILE "minishell_heredoc"

static int open_tempfile(void)
{
	int tmp_fd;

	tmp_fd = open(HEREDOC_TEMPFILE, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("minishell: heredoc: failed to create temporary file");
		return -1;
	}
	return tmp_fd;
}

static void write_to_tempfile(int tmp_fd, const char *input_line, ssize_t read_len)
{
	if (input_line[read_len - 1] != '\n')
	{
		char newline = '\n';
		write(tmp_fd, input_line, read_len);
		write(tmp_fd, &newline, 1);
	}
	else
	{
		write(tmp_fd, input_line, read_len);
	}
}

static void handle_heredoc_input(int tmp_fd, const char *marker)
{
	char *input_line;
	ssize_t read_len;

	input_line = malloc(HEREDOC_BUFFER_SIZE);
	if (!input_line)
	{
		perror("minishell: heredoc: memory allocation failed");
		close(tmp_fd);
		exit(1);
	}

	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		read_len = read(STDIN_FILENO, input_line, HEREDOC_BUFFER_SIZE);
		if (read_len == -1 || ft_strncmp(input_line, marker, ft_strlen(marker)) == 0)
			break;

		write_to_tempfile(tmp_fd, input_line, read_len);
	}

	free(input_line);
}

char *ft_heredoc_handler(char *marker)
{
	int tmp_fd;

	tmp_fd = open_tempfile();
	if (tmp_fd == -1)
		return NULL;

	handle_heredoc_input(tmp_fd, marker);
	close(tmp_fd);

	return ft_strdup(HEREDOC_TEMPFILE);
}