/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:54:07 by edouard           #+#    #+#             */
/*   Updated: 2024/08/20 11:23:21 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_exit(t_shell *shell)
{
	if (!shell->user_input)
	{
		if (isatty(STDIN_FILENO))
			printf(" exit\n");
		global_exit_env(shell, shell->last_exit_status);
	}
}
