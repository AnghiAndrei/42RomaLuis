/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:25:59 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/23 15:25:59 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*str_ret(int n, char *buffer)
{
	char		*p;

	p = malloc(n + 1);
	if (p == NULL)
		return (NULL);
	ft_strcpy(p, buffer);
	return (p);
}

char	*ret(int n, char *buffer, int fd)
{
	ssize_t			byteread;
	char			*p;

	p = str_ret((-n), buffer);
	if (p == NULL)
		return (NULL);
	byteread = read(fd, buffer, BUFFER_SIZE);
	if (*p == '\0' && byteread == 0)
	{
		free(p);
		return (NULL);
	}
	if (byteread == 0)
		return (p);
	if (byteread == -1)
	{
		free(p);
		return (NULL);
	}
	return (ft_strjoin(p, get_next_line(fd)));
}

char	*get_next_line(int fd)
{
	static char		buffer[1025][BUFFER_SIZE];
	int				n;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1025)
		return (NULL);
	if (buffer[fd][0] == '\n')
		return (str_ret(1, buffer[fd]));
	n = findn(buffer[fd]);
	if (n > 0)
		return (str_ret(n, buffer[fd]));
	else
		return (ret(n, buffer[fd], fd));
}
