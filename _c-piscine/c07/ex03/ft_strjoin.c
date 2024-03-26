/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:24:15 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/15 16:26:13 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	tot_len(int size, char **strs, char *sep)
{
	int	i;
	int	tot;

	i = 0;
	tot = 0;
	while (i < size)
	{
		tot = tot + ft_len(strs[i]);
		tot = tot + ft_len(sep);
		i++;
	}
	tot = tot - ft_len(sep);
	return (tot);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	char	*join;
	char	*join2;

	if (size == 0)
		return ((char *)malloc(sizeof(char)));
	join2 = (char *)malloc((tot_len(size, strs, sep) + 1));
	join = join2;
	if (!(join2))
		return (0);
	i = 0;
	while (i < size)
	{
		ft_strcpy(join2, strs[i]);
		join2 += ft_len(strs[i]);
		if (i < size - 1)
		{
			ft_strcpy(join2, sep);
			join2 += ft_len(sep);
		}
		i++;
	}
	*join2 = '\0';
	return (join);
}
