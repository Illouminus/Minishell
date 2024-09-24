/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:38:46 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 10:52:32 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HEREDOC_BUFFER_SIZE 1024
#define HEREDOC_TEMPFILE "minishell_heredoc"

void write_warning(char *arg)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

#include <signal.h>

void heredoc_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_cleanup_after_signal();
		close(STDIN_FILENO);
	}
}

static int open_tempfile(void)
{
	int tmp_fd;

	tmp_fd = open(HEREDOC_TEMPFILE, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("minishell: heredoc: failed to create temporary file");
		return (-1);
	}
	return tmp_fd;
}

static void write_to_tempfile(int tmp_fd, const char *input_line)
{
	size_t len;

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

void cleanup_heredoc(int fd, t_shell *shell)
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

static void handle_heredoc_input(int tmp_fd, char *marker,
											const char *heredoc_filename, t_shell *shell)
{
	char *line;

	//(void)shell;
	(void)heredoc_filename;
	signal(SIGINT, heredoc_sigint);
	while (g_exit_code != 130)
	{
		line = readline("> ");
		if (line && ft_strcmp(line, marker) == 0)
		{
			free(line);
			break;
		}
		if (line == NULL)
		{
			if (g_exit_code != 130)
				write_warning(marker);
			break;
		}
		write_to_tempfile(tmp_fd, line);
		free(line);
	}
	cleanup_heredoc(tmp_fd, shell);
}

char *ft_heredoc_handler(char *marker, t_shell *shell)
{
	int tmp_fd;
	char *temp_filename;

	shell->temp_stdin = dup(STDIN_FILENO);
	if (shell->temp_stdin == -1)
	{
		perror("minishell: heredoc: dup failed");
		return (NULL);
	}
	// Rajouter un check des tokens si le delimeter est valide ou pas (si c'est un mot ou pas)
	tmp_fd = open_tempfile();
	if (tmp_fd == -1)
	{
		close(shell->temp_stdin);
		return (NULL);
	}

	handle_heredoc_input(tmp_fd, marker, HEREDOC_TEMPFILE, shell);

	if (g_exit_code == 130)
	{
		unlink(HEREDOC_TEMPFILE); // Удаляем временный файл
		close(shell->temp_stdin);
		return (NULL); // Traiter le retour NULL plus haut dans le code - cést lui le seq fault
	}
	temp_filename = ft_strdup(HEREDOC_TEMPFILE);
	if (!temp_filename)
	{
		perror("minishell: heredoc: strdup failed");
		return (NULL);
	}
	return (temp_filename);
}