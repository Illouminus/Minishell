/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:56:44 by edouard           #+#    #+#             */
/*   Updated: 2024/06/27 12:07:23 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
int main(void)
{
	char *input;

	while (1)
	{
		display_prompt();
		input = readline(NULL);
		if (!input)
		{
			printf("exit\n");
			break;
		}
		add_history(input);
		free(input);
	}
	return 0;
}