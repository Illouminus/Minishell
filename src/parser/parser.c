/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/07/18 14:33:31 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Identfy commands and their arguments. Recognitiion of operators and pipes. Build an AST at the end
int parser(t_shell *shell)
{
	t_token *current_token; 

	if (!shell->user_input)
		return (EXIT_FAILURE);
	else if (ft_strcmp(shell->user_input, "/0") == 0)
		return (EXIT_FAILURE);
	else
	{
    	printf("RÉSULTAT DU PARSER\n");
		current_token = shell->token_list; 
		while (current_token != NULL)
		{
			if (current_token->tok_type == TOKEN_TYPE_CMD)
			{
				printf("Le token: %s est un %u\n", current_token->tok_value, current_token->tok_type); 
				// Création d'une instance de structure de commande 
			}
			else if (current_token->tok_type == TOKEN_TYPE_ARG)
			{
				printf("Le token: %s est un %u\n", current_token->tok_value, current_token->tok_type); 
				// On l'ajoute au tableau de tableau cmd_args de la commande qui précède cette arg
			}
			else 
			{
				printf("Nous avons reçu un pipe ou un redirect ou EOF\n"); 
				// La je sais pas trop
			}
			current_token = current_token->next_tok; 
		}
	}

	return (EXIT_SUCCESS);
}