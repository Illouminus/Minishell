/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:38:46 by edouard           #+#    #+#             */
/*   Updated: 2024/09/23 16:58:40 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEREDOC_BUFFER_SIZE 1024
#define HEREDOC_TEMPFILE "minishell_heredoc"

void	write_warning(char *arg)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}
void	heredoc_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		close(STDIN_FILENO);
	}
}
static int	open_tempfile(void)
{
	int	tmp_fd;

	tmp_fd = open(HEREDOC_TEMPFILE, O_CREAT | O_RDWR | O_TRUNC, 0600);
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
		{
			perror("minishell: heredoc: write failed");
		}
		if (write(tmp_fd, "\n", 1) == -1)
		{
			perror("minishell: heredoc: write failed");
		}
	}
	else
	{
		if (write(tmp_fd, input_line, len) == -1)
		{
			perror("minishell: heredoc: write failed");
		}
	}
}

static void	handle_heredoc_input(int tmp_fd, char *marker,
		char *heredoc_filename, t_shell *shell)
{
	char	*line;

	(void)heredoc_filename;
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (g_exit_code != 130)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_exit_code != 130)
				write_warning(marker);
			break ;
		}
		if (ft_strcmp(line, marker) == 0)
		{
			free(line);
			break ;
		}
		write_to_tempfile(tmp_fd, line);
		free(line);
	}
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (g_exit_code == 130)
	{
		unlink(HEREDOC_TEMPFILE);
		free_shell(shell);
		exit(shell->last_exit_status);
		//printf("G exit code: %d\n", g_exit_code);
	}
	else
	{
		// Закрываем временный файл после записи
		close(tmp_fd);
	}
}

char	*ft_heredoc_handler(char *marker, t_shell *shell)
{
	int	tmp_fd;

	//shell->temp_stdin = dup(STDIN_FILENO);
	tmp_fd = open_tempfile();
	if (tmp_fd == -1)
		return (NULL);
	handle_heredoc_input(tmp_fd, marker, HEREDOC_TEMPFILE, shell);
	//printf("G exit code: %d\n", g_exit_code);
	if (g_exit_code == 130)
	{
		close(tmp_fd);
		unlink(HEREDOC_TEMPFILE);
		free_shell(shell); // Удаляем временный файл при прерывании
		return (NULL);
	}
	close(tmp_fd);
	//dup2(shell->temp_stdin, STDIN_FILENO);
	//close(shell->temp_stdin);
	return (ft_strdup(HEREDOC_TEMPFILE));
}
