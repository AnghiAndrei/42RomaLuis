/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & pfalasch <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:10:39 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/03/08 18:10:40 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd, char *string)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (!ft_strchr(string, '\n'))
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1 || i == 0)
			break ;
		temp[i] = '\0';
		string = ft_gnl_strjoin(string, temp);
	}
	free(temp);
	if (ft_strlen(string) == 0)
	{
		free(string);
		return (NULL);
	}
	return (string);
}

char	*get_next_line(int fd)
{
	static char	*save[257];
	char		*ret;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save[fd])
		save[fd] = ft_strdup("");
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	ret = ft_gnl_substr(save[fd], 0, ft_search(save[fd], '\n') + 1, 0);
	save[fd] = ft_gnl_substr(save[fd], ft_search(save[fd], '\n') + 1,
			ft_strlen(save[fd]), 1);
	return (ret);
}
