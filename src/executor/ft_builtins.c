/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahors <ahors@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:09:40 by ahors             #+#    #+#             */
/*   Updated: 2024/07/17 13:13:07 by ahors            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// EXPORT | Affiche l'env 
void ft_export(t_shell *shell)
{
    t_env *current = shell->env_var_list;
    while (current != NULL)
    {
        printf("%s: %s\n", current->env_var_name, current->env_value);
        current = current->next_env;
    }
}