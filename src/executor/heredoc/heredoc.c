/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:38:46 by edouard           #+#    #+#             */
/*   Updated: 2024/09/30 10:42:32 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEREDOC_BUFFER_SIZE 1024
#define HEREDOC_TEMPFILE "minishell_heredoc"

static int	open_tempfile(char *temp_filename)
{
	int	tmp_fd;

	tmp_fd = open(temp_filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("minishell: heredoc: failed to create temporary file");
		return (-1);
	}
	return (tmp_fd);
}

static void	write_to_tempfile(int tmp_fd, const char *input_line)
{
	size_t	len;

	len = strlen(input_line);
	if (len > 0 && input_line[len - 1] != '\n')
	{
		if (write(tmp_fd, input_line, len) == -1)
			perror("minishell: heredoc: write failed");
		if (write(tmp_fd, "\n", 1) == -1)
			perror("minishell: heredoc: write failed");
	}
	else
	{
		if (write(tmp_fd, input_line, len) == -1)
			perror("minishell: heredoc: write failed");
	}
}

void	cleanup_heredoc(int fd, t_shell *shell)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
			perror("minishell: heredoc: failed to close temporary file");
	}
	close(STDIN_FILENO);
	if (dup2(shell->temp_stdin, STDIN_FILENO) == -1)
		perror("minishell: heredoc: dup2 failed");
	if (close(shell->temp_stdin) == -1)
		perror("minishell: heredoc: failed to close temp_stdin");
}

static void	handle_heredoc_input(int tmp_fd, char *marker, t_shell *shell)
{
	char	*line;

	signal(SIGINT, heredoc_sigint);
	while (g_exit_code != 130)
	{
		line = readline("> ");
		if (line && ft_strcmp(line, marker) == 0)
		{
			free(line);
			break ;
		}
		if (line == NULL)
		{
			if (g_exit_code != 130)
				exit_by_signal(marker);
			break ;
		}
		write_to_tempfile(tmp_fd, line);
		free(line);
	}
	cleanup_heredoc(tmp_fd, shell);
}

char	*ft_heredoc_handler(char *marker, t_shell *shell)
{
	int		tmp_fd;
	char	*temp_filename;

	if (!is_valid_heredoc_delimiter(marker))
		return (NULL);
	shell->temp_stdin = dup(STDIN_FILENO);
	if (shell->temp_stdin == -1)
		return (NULL);
	temp_filename = ft_generate_unique_heredoc_filename(shell);
	tmp_fd = open_tempfile(temp_filename);
	handle_heredoc_input(tmp_fd, marker, shell);
	if (g_exit_code == 130)
	{
		unlink(temp_filename);
		free(temp_filename);
		close(shell->temp_stdin);
		return (NULL);
	}
	close(tmp_fd);
	close(shell->temp_stdin);
	return (temp_filename);
}
