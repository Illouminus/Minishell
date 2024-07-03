/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:54:07 by edouard           #+#    #+#             */
/*   Updated: 2024/07/03 18:19:16 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_exit(t_shell *shell)
{
	if (!shell->user_input)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 5);
		global_exit(shell, shell->last_exit_status);
	}
}
