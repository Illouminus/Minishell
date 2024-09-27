/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:44:48 by ebaillot          #+#    #+#             */
/*   Updated: 2024/09/27 14:47:31 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_segments(char **segments)
{
	int	i;

	i = 0;
	if (segments)
	{
		while (segments[i])
		{
			free(segments[i]);
			i++;
		}
		free(segments);
	}
}

char	**split_path_segments(const char *path)
{
	char	**segments;

	segments = ft_split(path, '/');
	return (segments);
}

char	*combine_paths(const char *current_path, const char *path)
{
	char	*combined;
	char	*temp;

	combined = ft_strjoin(current_path, "/");
	if (!combined)
		return (NULL);
	temp = ft_strjoin(combined, path);
	free(combined);
	if (!temp)
		return (NULL);
	return (temp);
}

void	process_segment(const char *segment, char **stack, int *top)
{
	if (ft_strcmp(segment, ".") == 0)
	{
	}
	else if (ft_strcmp(segment, "..") == 0)
	{
		if (*top >= 0)
			(*top)--;
	}
	else
	{
		(*top)++;
		stack[*top] = (char *)segment;
	}
}

char	**duplicate_stack(char **stack, int top)
{
	char	**resolved;
	int		j;

	resolved = (char **)malloc((top + 2) * sizeof(char *));
	if (!resolved)
		return (NULL);
	j = 0;
	while (j <= top)
	{
		resolved[j] = ft_strdup(stack[j]);
		if (!resolved[j])
		{
			while (j > 0)
				free(resolved[--j]);
			free(resolved);
			return (NULL);
		}
		j++;
	}
	resolved[j] = NULL;
	return (resolved);
}
