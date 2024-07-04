/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/07/04 13:05:59 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parser(t_shell *shell)
{
	if (!shell->user_input)
		return (1);
	else if (ft_strcmp(shell->user_input, "/0") == 0)
		return 1;
	return 0;
}