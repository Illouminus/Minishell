/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/07/18 15:35:10 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cmd_is_built_in(char *value)
{
	if (ft_strcmp(value, "cd") == 0)
		return (1); 
	else if (ft_strcmp(value, "pwd") == 0)
		return (1);
	return (0);
}

t_command	*ft_new_command_init(t_command *command, t_command *last_command, t_token *current_token)
{
	command = malloc(sizeof(t_command));
	 if (!command) 
	{
		printf("Error in parser, during malloc for a new_command\n");
		return (NULL);
	}
	command->cmd_args = malloc(2 * sizeof(char *));
	command->cmd_value = strdup(current_token->tok_value);
	command->is_builtin_cmd = ft_cmd_is_built_in(current_token->tok_value);
	command->redir_tokens = NULL;
	command->next_cmd = NULL;
	command->prev_cmd = last_command;
	return (command); 
}

//Juste de l'affichage temporaire
void 	ft_display_command_resume(t_command *command)
{
	if (command->is_builtin_cmd)
		printf("La commande %s est built-in. Elle pointe sur %s\n\n", command->cmd_value); 
	else
		printf("La commande %s n'est pas built-in\n\n", command->cmd_value); 
}

// Identfy commands and their arguments. Recognitiion of operators and pipes. Build an AST at the end
int parser(t_shell *shell)
{
	t_token		*current_token; 
	t_command	*new_command; 
	t_command	*last_command; 
	

	last_command = NULL; 
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
			// Création d'une nouvelle instance de structure de commande
			if (current_token->tok_type == TOKEN_TYPE_CMD)
			{
				printf("Le token: %s est un %u\n", current_token->tok_value, current_token->tok_type); 
				// Création d'une instance de structure de commande  || Voir la fonction ci-dessus command init
				new_command = ft_new_command_init(new_command, last_command, current_token); 
				//On définit le pointeur de shell->command_list pour pointer sur notre 1ère commande et lié shell->command_list à notre liste chaînée de commandes
				if(shell->command_list == NULL && last_command == NULL)
					shell->command_list = new_command; 
				// Si last_command n'est pas égal ==> Nous avons déja créer une commande, donc nous sommes apès un pipe par exemple
				if (last_command != NULL)
				{
					new_command->prev_cmd = last_command; // Dont est égal à NULL  
					last_command->next_cmd = new_command; 
				}
				// Sinon nous sommes à la 1ère commande, dans ce cas il n'y a pas encore de next vers lequel pointé
				else
				{
					new_command->prev_cmd = last_command; // Donc est égal à NULL  
					new_command->next_cmd = NULL; 
				}
				ft_display_command_resume(new_command); 
			}
			else if (current_token->tok_type == TOKEN_TYPE_ARG)
			{
				printf("Le token: %s est un %u\n", current_token->tok_value, current_token->tok_type); 
				// On l'ajoute au tableau de tableau cmd_args de la commande correspondante
				
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