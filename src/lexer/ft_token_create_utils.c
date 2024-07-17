/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:50:44 by ahors             #+#    #+#             */
/*   Updated: 2024/07/17 13:45:55 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// Fonction pour creer et ajouter un token de type commande
void ft_create_add_command_token(t_shell *shell, char *value, int quote_status)
{
    ft_add_token(shell, ft_create_token(TOKEN_TYPE_CMD, value, quote_status));
}

// Fonction pour creer et ajouter un token de type argument
void ft_create_add_argument_token(t_shell *shell, char *value, int quote_status) 
{
    ft_add_token(shell, ft_create_token(TOKEN_TYPE_ARG, value, quote_status));
}

// Fonction pour creer et ajouter un token de type redirection
void ft_create_add_redirection_token(t_shell *shell, char *value, int quote_status) 
{
    ft_add_token(shell, ft_create_token(TOKEN_TYPE_REDIR, value, quote_status));
}

// Fonction pour creer et ajouter un token de type pipe
void ft_create_add_pipe_token(t_shell *shell) 
{
    ft_add_token(shell, ft_create_token(TOKEN_TYPE_PIPE, "|", 0));
}