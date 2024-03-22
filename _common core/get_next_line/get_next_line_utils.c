/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:26:04 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/30 11:22:39 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcpy(char *dest, char *src)
{
	int		i;
	int		i2;

	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i] = '\n';
		i++;
	}
	dest[i] = '\0';
	i2 = 0;
	while (src[i2] != '\0')
	{
		src[i2] = src[i2 + i];
		i2++;
	}
	src[i2] = '\0';
}

int	findn(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (i * -1);
	i++;
	return (i);
}

int	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		i2;
	char		*s3;

	if (!(s1 && s2))
		return (NULL);
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	i2 = 0;
	while (s2[i2])
	{
		s3[i + i2] = s2[i2];
		i2++;
	}
	s3[i + i2] = '\0';
	free(s1);
	free(s2);
	return (s3);
}
