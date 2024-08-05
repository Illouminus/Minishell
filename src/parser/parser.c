/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:18:35 by edouard           #+#    #+#             */
/*   Updated: 2024/08/05 15:37:02 by adrienhors       ###   ########.fr       */
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

t_command	*ft_new_command_init(t_command *command, t_token *current_token, int nb_of_args)
{
	command = malloc(sizeof(t_command));
	if (!command) 
	{
		printf("Error in parser, during new_command_init\n");
		return (NULL);
	}
	command->cmd_value = ft_strdup(current_token->tok_value);
	command->cmd_args = malloc(nb_of_args * sizeof(char *));
	command->is_builtin_cmd = ft_cmd_is_built_in(current_token->tok_value);
	command->redir_tokens = NULL;
	return (command); 
}

void ft_afficher_cmd_args(char **cmd_args, int len) 
{
	int i; 

    if (cmd_args == NULL) 
	{
        printf("Le tableau est vide.\n");
        return;
    }
    
	i = 0; 
	while (i < len)
	{
        printf("cmd_args[%d]: %s\n", i, cmd_args[i]);
		i++;
    }
}

// Fonction pour afficher une liste de commandes
void ft_afficher_command_list(t_command *command_list, int i ) 
{
    t_command *current_command = command_list;
    int index;
    
	index = 0; 
    while (current_command)
	{
        printf("Commande numéro %d:\n", index);
        printf("  cmd_value: %s\n", current_command->cmd_value);
        printf("  is_builtin_cmd: %s\n", current_command->is_builtin_cmd ? "true" : "false");
        printf("  cmd_args:\n");
        ft_afficher_cmd_args(current_command->cmd_args, i);
        
        current_command = current_command->next_cmd;
        index++;
    }
}

// Identfy commands and their arguments. Recognitiion of operators and pipes. Build an AST at the end
int parser(t_shell *shell)
{
	t_token		*current_token; 
	t_token		*tmp_token; 
	t_command	*new_command; 
	t_command	*last_command; 
	int	cmd_nb_args; 
	int i; 
	

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
				cmd_nb_args = 0;
				tmp_token = current_token->next_tok; 
				while (tmp_token != NULL && tmp_token->tok_type == TOKEN_TYPE_ARG)
				{
					cmd_nb_args++;
					tmp_token = tmp_token->next_tok;
				}
				// Création d'une instance de structure de commande  || Voir la fonction ci-dessus command init
				new_command = ft_new_command_init(new_command, current_token, cmd_nb_args); 
				if (!new_command)
					return (EXIT_FAILURE);
				//On définit le pointeur de shell->command_list pour pointer sur notre 1ère commande et lié shell->command_list à notre liste chaînée de commandes
				if(shell->command_list == NULL && last_command == NULL)
				{
					shell->command_list = new_command; 
					new_command->prev_cmd = last_command; // Donc est égal à NULL  
					new_command->next_cmd = NULL; 
				}
				// Si last_command n'est pas égal ==> Nous avons déja créer une commande, donc nous sommes apès un pipe par exemple
				else
				{
					new_command->prev_cmd = last_command; 
					last_command->next_cmd = new_command; 
				}
				last_command = new_command;
				i = 0;
			}
			else if (current_token->tok_type == TOKEN_TYPE_ARG)
			{
				last_command->cmd_args[i] = ft_strdup(current_token->tok_value);
				i++;
			}
			else 
			{
				//Créer une instance de commande, qui en soit n'est pas une commande avec une commande value à "pipe"
				if (current_token->tok_type == TOKEN_TYPE_PIPE)
				{
					new_command = ft_new_command_init(new_command, current_token, 0); 	
					if (!new_command)
                        return (EXIT_FAILURE); 
					new_command->prev_cmd = last_command;  
					last_command->next_cmd = new_command; 
				}
			}
			current_token = current_token->next_tok;
		}
		if (last_command != NULL)
			last_command->cmd_args[i] = NULL; // Ensure the last command args are properly terminated
        ft_afficher_command_list(shell->command_list, i);
	}
	
	 
	return (EXIT_SUCCESS);
}