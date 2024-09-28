/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_outils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:26:04 by edouard           #+#    #+#             */
/*   Updated: 2024/09/28 16:04:16 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void heredoc_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		rl_cleanup_after_signal();
		close(STDIN_FILENO);
	}
}

static int is_valid_delimiter_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '-');
}

void exit_by_signal(char *arg)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `",
					 STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

int is_valid_heredoc_delimiter(const char *delimiter)
{
	if (!delimiter || *delimiter == '\0')
		return (0);
	while (*delimiter)
	{
		if (!is_valid_delimiter_char(*delimiter))
			return (0);
		delimiter++;
	}
	return (1);
}

char *ft_generate_unique_heredoc_filename(t_shell *shell)
{
	char *temp_file;
	char *temp_num;
	char *full_filename;

	shell->heredoc_counter++;
	temp_num = ft_itoa(shell->heredoc_counter);
	if (!temp_num)
	{
		perror("ft_itoa failed");
		return NULL;
	}
	temp_file = ft_strjoin("/tmp/minishell_heredoc_", temp_num);
	free(temp_num);
	if (!temp_file)
	{
		perror("ft_strjoin failed");
		return NULL;
	}
	full_filename = ft_strdup(temp_file);
	free(temp_file);
	if (!full_filename)
	{
		return NULL;
	}
	return full_filename;
}
