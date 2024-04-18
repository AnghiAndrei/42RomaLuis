/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everolla <everolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:49:59 by pcoletta          #+#    #+#             */
/*   Updated: 2024/03/13 18:19:11 by everolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcontains(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char *s1, char *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*tmp;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (!ft_strcontains(s1[start], set))
		start++;
	while (start - 1 != end && !ft_strcontains(s1[end], set))
		end--;
	if (start - 1 == end)
	{
		tmp = malloc(sizeof(char));
		if (tmp == NULL)
			return (NULL);
		tmp[0] = '\0';
		return (tmp);
	}
	return (ft_substr(s1, start, end - start + 1));
}
