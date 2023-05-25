/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmuminov <nmuminov@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:16:25 by nmuminov          #+#    #+#             */
/*   Updated: 2022/12/21 16:34:56 by nmuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *stash)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		stash = ft_strjoin_free(stash, buffer);
		if (ft_find_new_line(stash) >= 0)
			break ;
	}
	free(buffer);
	return (stash);
}

char	*ft_line(char *stash)
{
	char	*line;
	int		i;

	if (stash[0] == '\0')
		return (NULL);
	i = ft_find_new_line(stash);
	if (i == -1)
		i = ft_strlen(stash) - 1;
	line = malloc(i + 2);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, stash, i + 1);
	line[i + 1] = '\0';
	return (line);
}

char	*ft_new_stash(char *stash)
{
	char	*new_stash;
	int		i;

	i = ft_find_new_line(stash);
	if (i == -1)
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(ft_strlen(stash) - i);
	if (new_stash == NULL)
		return (NULL);
	ft_memcpy(new_stash, stash + i + 1, ft_strlen(stash + i + 1) + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = ft_line(stash);
	stash = ft_new_stash(stash);
	return (line);
}
