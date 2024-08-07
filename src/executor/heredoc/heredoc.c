/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:38:46 by edouard           #+#    #+#             */
/*   Updated: 2024/08/06 17:01:38 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_heredoc_handler(t_command *command, t_shell *shell)
{
	char *marker;
	char *input_line;
	size_t len;
	ssize_t read_len;
	int tmp_fd;

	marker = command->heredoc_marker;
	input_line = malloc(1024);
	if (!input_line)
		return (1);
	shell->heredoc_tempfile = ft_strdup("/tmp/minishell_heredoc");
	tmp_fd = open(shell->heredoc_tempfile, O_CREAT | O_RDWR | O_TRUNC, 0600);
	len = 1024;
	if (tmp_fd == -1)
	{
		free(input_line);
		return (1);
	}

	printf("heredoc> ");

	while ((read_len = read(STDIN_FILENO, input_line, len)) > 0)
	{
		input_line[read_len] = '\0';

		if (ft_strncmp(input_line, marker, strlen(marker)) == 0)
			break;

		write(tmp_fd, input_line, read_len);
		printf("heredoc> ");
	}

	free(input_line);
	close(tmp_fd);

	tmp_fd = open(shell->heredoc_tempfile, O_RDONLY);
	if (tmp_fd == -1)
		perror("open tempfile failed");

	if (dup2(tmp_fd, STDIN_FILENO) == -1)
		perror("dup2 failed");

	close(tmp_fd);
	unlink(shell->heredoc_tempfile);
	return (0);
}
