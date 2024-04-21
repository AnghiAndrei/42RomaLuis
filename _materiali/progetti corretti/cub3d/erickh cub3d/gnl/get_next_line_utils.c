/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebraho <ebraho@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:03:51 by ccolaiac          #+#    #+#             */
/*   Updated: 2022/09/15 16:06:59 by ebraho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

int	ft_search(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

char	*ft_gnl_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = ((char *)malloc(sizeof(char) * ft_strlen(s1) + 1));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_gnl_substr(char *s, unsigned int start, size_t len, int need_free)
{
	size_t	i;
	char	*str;

	if (!s)
		return (0);
	i = 0;
	if (ft_strlen(s) <= len)
		str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (start < (unsigned int) ft_strlen(s))
	{
		while (i < len && s[start] != '\0')
		{
			str[i] = s[start];
			i++;
			start++;
		}
	}
	str[i] = '\0';
	if (need_free)
		free(s);
	return (str);
}
