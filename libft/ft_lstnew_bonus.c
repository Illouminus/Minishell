/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:16:06 by edouard           #+#    #+#             */
/*   Updated: 2023/12/21 13:30:15 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*loc;

	loc = malloc(sizeof(t_list));
	if (!loc)
		return (NULL);
	loc->content = content;
	loc->next = NULL;
	return (loc);
}
