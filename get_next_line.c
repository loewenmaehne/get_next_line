/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzienert <jzienert@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:18:55 by jzienert          #+#    #+#             */
/*   Updated: 2025/07/03 15:47:09 by jzienert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

void	ft_free_and_set_null(char **p)
{
	if (*p)
		free(*p);
	*p = NULL;
}

// looks for '\n' and creates a new str with
// the whole rest beyond that character
// frees the old stash first to malloc the new content
void	ft_remove_line_from(char **stash)
{
	ssize_t	llen;
	ssize_t	rlen;
	char	*new_stash;

	if (!stash || !*stash)
		return ;
	llen = 0;
	while ((*stash)[llen] && (*stash)[llen] != '\n')
		llen++;
	if ((*stash)[llen] == '\n')
		llen++;
	rlen = ft_strlen(*stash + llen);
	if (rlen == 0)
		return (ft_free_and_set_null(stash));
	new_stash = malloc(rlen + 1);
	if (!new_stash)
		return (ft_free_and_set_null(stash));
	ft_strlcpy(new_stash, *stash + llen, rlen + 1);
	ft_free_and_set_null(stash);
	*stash = new_stash;
}

// Reads into the buffer when called and appends
// to stash.
// returns: number of bytes read and added to stash
//			and for error -1
ssize_t	ft_read_and_update(int fd, char **stash)
{
	char		*buffer;
	char		*new_stash;
	ssize_t		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 1)
		free(buffer);
	if (bytes == 0)
		return (0);
	if (bytes < 0)
		return (-1);
	buffer[bytes] = '\0';
	if (!*stash)
		*stash = buffer;
	else
	{
		new_stash = ft_strjoin((const char *) *stash, buffer);
		free(buffer);
		free(*stash);
		*stash = new_stash;
	}
	return (bytes);
}

// Extracts the first line from stash including '\n'
// If no newline character has been found
// the rest of the stash gets returned.
// returns: new malloced first line or rest, null terimnated.
char	*ft_extract_line(char *stash)
{
	char	*line;
	ssize_t	llen;

	if (!stash)
		return (NULL);
	llen = 0;
	while (stash[llen] && stash[llen] != '\n')
		llen++;
	if (stash[llen] == '\n')
		llen++;
	line = malloc(llen + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, llen + 1);
	return (line);
}

// Reads one line at a time from a file descriptor
char	*get_next_line(int fd)
{
	static char		*stash;
	char			*line;
	ssize_t			bytes;

	line = NULL;
	bytes = 1;
	if (BUFFER_SIZE < 1 || fd < 0 || !BUFFER_SIZE)
		return (NULL);
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = ft_read_and_update(fd, &stash);
		if (bytes < 0)
		{
			ft_free_and_set_null(&stash);
			free(line);
			return (NULL);
		}
	}
	line = ft_extract_line(stash);
	if (!line)
		ft_free_and_set_null(&stash);
	ft_remove_line_from(&stash);
	return (line);
}
