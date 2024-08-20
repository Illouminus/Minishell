/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:38:46 by edouard           #+#    #+#             */
/*   Updated: 2024/08/20 11:34:39 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_heredoc_handler(char *marker)
{
	char *input_line;
	size_t len = 1024;
	ssize_t read_len;
	char *tempfile_path = ft_strdup("minishell_heredoc");
	int tmp_fd = open(tempfile_path, O_CREAT | O_RDWR | O_TRUNC, 0600);

	if (tmp_fd == -1)
		return NULL; // Обработка ошибки

	input_line = malloc(len);
	if (!input_line)
		return NULL;

	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		read_len = read(STDIN_FILENO, input_line, len);
		if (read_len == -1 || ft_strncmp(input_line, marker, ft_strlen(marker)) == 0)
			break;

		// Добавляем \n в конец каждой строки, если его нет
		if (input_line[read_len - 1] != '\n')
		{
			input_line[read_len] = '\n';
			read_len++;
		}

		write(tmp_fd, input_line, read_len);
	}

	free(input_line);
	close(tmp_fd);
	return tempfile_path;
}