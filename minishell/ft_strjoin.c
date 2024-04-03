/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:17:36 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/03 15:02:25 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		i2;
	char		*s3;

	if (!(s1 && s2))
		return (NULL);
	s3 = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
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
	return (s3);
}

char	*ft_strjoin12f(char *s1, char *s2)
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

char	*ft_strjoin1f(char *s1, char *s2)
{
	size_t		i;
	size_t		i2;
	char		*s3;

	if (!(s1 && s2))
		return (NULL);
	s3 = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
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
	return (s3);
}

char	*ft_strjoin2f(char *s1, char *s2)
{
	size_t		i;
	size_t		i2;
	char		*s3;

	if (!(s1 && s2))
		return (NULL);
	s3 = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
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
	free(s2);
	return (s3);
}
