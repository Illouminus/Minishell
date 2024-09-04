/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:03:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/04 13:45:47 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_remaining(char *stash)
{
	int		i;
	char	*remaining;
	int		len;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		i++;
	len = 0;
	while (stash[i + len])
		len++;
	remaining = malloc(len + 1);
	if (!remaining)
		return (free(stash), NULL);
	remaining = ft_strncpy(remaining, stash + i, len);
	free(stash);
	return (remaining);
}

char	*exrtact_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!*stash)
		return (free(stash), NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	if (!line)
		return (free(line), NULL);
	return (line);
}

char	*read_from_file(char *stash, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!stash)
			return (free(stash), free(buffer), NULL);
		free(stash);
		stash = temp;
	}
	free(buffer);
	if (bytes_read == 0 && stash && *stash == '\0')
		return (free(stash), NULL);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0))
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = read_from_file(stash, fd);
	if (!stash)
		return (NULL);
	line = exrtact_line(stash);
	if (!line)
		return (free(stash), NULL);
	stash = get_remaining(stash);
	return (line);
}
