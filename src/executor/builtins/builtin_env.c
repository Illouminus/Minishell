/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:17 by edouard           #+#    #+#             */
/*   Updated: 2024/08/30 10:55:49 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_builtin_env(t_env *env)
{
	ft_print_env_list(env);
	return (EXIT_SUCCESS);
}

void handle_error_non_critical(const char *cmd, const char *error_message, int exit_code, t_shell *shell)
{
	fprintf(stderr, "minishell: %s: %s\n", cmd, error_message);
	shell->last_exit_status = exit_code;
}