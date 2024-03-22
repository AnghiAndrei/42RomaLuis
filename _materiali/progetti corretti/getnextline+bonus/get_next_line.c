/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:27:17 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/26 11:45:08 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_line(int fd, char *stc_backup)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bytes_read > 0 && !ft_strchr(stc_backup, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stc_backup = ft_strjoin(stc_backup, buffer);
	}
	free(buffer);
	return (stc_backup);
}

static char	*extract_line(char *stc_backup)
{
	char	*line;			
	int		i;

	if (!stc_backup[0])
		return (NULL);
	i = 0;
	while (stc_backup[i] != '\n' && stc_backup[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stc_backup[i] != '\n' && stc_backup[i] != '\0')
	{
		line[i] = stc_backup[i];
		i++;
	}
	if (stc_backup[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_stc_string(char *stc_backup)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (stc_backup[i] != '\n' && stc_backup[i])
		i++;
	if (stc_backup[i] == '\0')
	{
		free(stc_backup);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(stc_backup) - i + 1));
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (stc_backup[i])
		tmp[j++] = stc_backup[i++];
	tmp[j] = '\0';
	free(stc_backup);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*line;	
	static char	*stc_backup;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stc_backup = find_line(fd, stc_backup);
	if (!stc_backup)
		return (NULL);
	line = extract_line(stc_backup);
	stc_backup = update_stc_string(stc_backup);
	return (line);
}
