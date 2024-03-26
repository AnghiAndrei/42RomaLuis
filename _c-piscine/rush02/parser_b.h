/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_b.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:49:53 by apuddu            #+#    #+#             */
/*   Updated: 2023/11/12 21:49:56 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_realloc(char *buf, int buf_size, int new_size)
{
	char	*new_b;
	int		i;

	new_b = (char *)malloc(new_size);
	i = 0;
	while (i < buf_size)
	{
		new_b[i] = buf[i];
		i++;
	}
	free(buf);
	return (new_b);
}

int	do_i_break(int fd, char *buf, int i, int *eof)
{
	if (read(fd, buf + i, 1) != 1)
	{
		*eof = 1;
		return (1);
	}
	if (buf[i] == '\n')
		return (1);
	return (0);
}

ssize_t	ft_getline(int fd, char **dest, int *eof)
{
	int		sz;
	char	*buf;
	ssize_t	i;

	sz = 32;
	buf = (char *)malloc(32);
	i = 0;
	while (1)
	{
		if (do_i_break(fd, buf, i, eof))
			break ;
		if (i == sz - 1)
		{
			buf = ft_realloc(buf, sz, sz * 2);
			sz *= 2;
		}
		i++;
	}
	buf[i] = '\0';
	*dest = buf;
	return (i + 1);
}
