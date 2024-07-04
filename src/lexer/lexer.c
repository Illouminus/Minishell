/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:38:33 by edouard           #+#    #+#             */
/*   Updated: 2024/07/04 16:17:37 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lexer(t_shell *shell)
{

	printf("User input: %s\n", shell->user_input);

	if (!shell->user_input)
		return (EXIT_FAILURE);
	else if (ft_strcmp(shell->user_input, "/0") == 0)
		return (EXIT_FAILURE);
	add_history(shell->user_input);
	return 0;
}