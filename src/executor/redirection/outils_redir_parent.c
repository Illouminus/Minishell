/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_redir_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:52:32 by edouard           #+#    #+#             */
/*   Updated: 2024/09/30 11:07:56 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_standard_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
	{
		perror("dup failed for STDIN");
		return (-1);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		perror("dup failed for STDOUT");
		close(*saved_stdin);
		return (-1);
	}
	return (0);
}

int	restore_standard_fds(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2 failed to restore STDIN");
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed to restore STDOUT");
	}
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}

int	validate_and_open_redirections(t_command *current, t_shell *shell)
{
	t_redir	*redir;

	redir = current->redirections;
	while (redir)
	{
		if (open_redirection(redir, shell) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

char	*ft_getenv(t_env *env_list, const char *name)
{
	t_env	*var;

	var = ft_get_env_var_by_name(env_list, name);
	if (var)
	{
		return (strdup(var->env_value));
	}
	return (NULL);
}
