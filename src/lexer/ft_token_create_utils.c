/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:50:44 by ahors             #+#    #+#             */
/*   Updated: 2024/07/17 15:14:49 by ahors            ###   ########.fr       */
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

// Fonction pour creer et ajouter un token de type redirection in
void ft_create_add_redirection_in_token(t_shell *shell, char *value, int quote_status) 
{
    ft_add_token(shell, ft_create_token(TOKEN_TYPE_REDIR_IN, value, quote_status));
}

// Fonction pour creer et ajouter un token de type redirection out
void ft_create_add_redirection_out_token(t_shell *shell, char *value, int quote_status) 
{
    ft_add_token(shell, ft_create_token(TOKEN_TYPE_REDIR_OUT, value, quote_status));
}

// Fonction pour creer et ajouter un token de type pipe
void ft_create_add_pipe_token(t_shell *shell) 
{
    ft_add_token(shell, ft_create_token(TOKEN_TYPE_PIPE, "|", 0));
}