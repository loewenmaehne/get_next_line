/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzienert <jzienert@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:23:29 by jzienert          #+#    #+#             */
/*   Updated: 2025/07/03 15:42:42 by jzienert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Added if(!s) check. Not present in libft.
char	*ft_strchr(const char *s, int c)
{
	char	c1;

	if (!s)
		return (NULL);
	c1 = (char) c;
	while (*s && *s != c1)
		s++;
	if (*s == c1 || !s)
		return ((char *) s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

// s1 = stash (dst)
// s2 = buffer (src)
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ps;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ps = malloc(s1len + s2len + 1);
	if (!ps)
		return (NULL);
	ft_strlcpy(ps, s1, s1len + 1);
	ft_strlcpy(ps + s1len, s2, s2len + 1);
	return (ps);
}
