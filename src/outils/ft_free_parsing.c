/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrienhors <adrienhors@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:04:29 by adrienhors        #+#    #+#             */
/*   Updated: 2024/08/06 16:29:14 by adrienhors       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Fonction pour free le tableau d'args
void    ft_free_commands_args(char **args)
{
    int i; 

    i = 0;
    while (args[i])
    {
        free(args[i]); 
        i++;
    }
    free(args);
}

int ft_determine_len_cmd_args(char **cmd_args)
{
    int i; 

    i = 0;
    while (cmd_args[i + 1])
        i++;
    return (i);
}


// Fonction pour libérer les arguments de la commande
void ft_free_cmd_args(char **cmd_args) 
{
    int i;
    int len_cmd_args; 
    
    if (cmd_args == NULL)
    {
        printf("cmd_args est NULL\n");
        return;
    }
    
    i = 0; 
    len_cmd_args = ft_determine_len_cmd_args(cmd_args);
    while (i < len_cmd_args)
    {
        free(cmd_args[i]);
        i++;
    }
    free(cmd_args);
}

// Fonction pour libérer une liste de commandes
void ft_free_command_list(t_command *command_list) 
{
    t_command *current_command = command_list;
    t_command *next_command;
    
    while (current_command->next_cmd != NULL) 
    {
        next_command = current_command->next_cmd;
        if (current_command->cmd_value != NULL) {
            free(current_command->cmd_value);
        }
        
        ft_free_cmd_args(current_command->cmd_args);
        
        free(current_command);
        current_command = next_command;
    }
    free(command_list); 
}