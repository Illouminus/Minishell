/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_outils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:26:04 by edouard           #+#    #+#             */
/*   Updated: 2024/09/27 18:12:49 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		//ft_putstr_fd("\n", STDOUT_FILENO);
		rl_cleanup_after_signal();
		close(STDIN_FILENO);
	}
}

static int	is_valid_delimiter_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '-');
}

void	exit_by_signal(char *arg)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

int	is_valid_heredoc_delimiter(const char *delimiter)
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
