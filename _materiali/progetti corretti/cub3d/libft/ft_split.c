/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everolla <everolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:48:02 by pcoletta          #+#    #+#             */
/*   Updated: 2024/03/13 18:20:23 by everolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_splits(char *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	size_t			amount;

	if (s == NULL)
		return (-2);
	if (s[0] == '\0')
		return (0);
	i = 1;
	j = 0;
	amount = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (i - 1 != j)
				amount++;
			j = i;
		}
		i++;
	}
	if (s[i - 1] != c)
		amount++;
	return (amount);
}

int	ft_find_after(char *s, char to_find, unsigned int after)
{
	unsigned int	i;

	i = after;
	while (s[i] != '\0')
	{
		if (s[i] == to_find)
			return (i);
		i++;
	}
	return (ft_strlen(s));
}

char	**ft_split(char *s, char c)
{
	size_t			size;
	char			**splits;
	unsigned int	i;
	int				j;
	int				k;

	size = ft_count_splits(s, c);
	splits = malloc(sizeof(char *) * (size + 1));
	if (splits == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		k = ft_find_after(s, c, j);
		if (k != j)
		{
			splits[i] = ft_substr(s, j, k - j);
			i++;
		}
		j = k + 1;
	}
	splits[i] = NULL;
	return (splits);
}
