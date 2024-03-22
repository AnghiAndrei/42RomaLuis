/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:51:15 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/10 23:51:15 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*start_mag(void)
{
	char	*s2;

	s2 = (char *)malloc(1);
	if (s2 == NULL)
		return (NULL);
	s2[0] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= (unsigned int)ft_strlen((char *)s))
		return (start_mag());
	if (len > (unsigned int)ft_strlen((char *)s + start))
		len = ft_strlen((char *)s + start);
	s2 = (char *)malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s[i + start] != '\0' && i < len)
	{
		s2[i] = s[i + start];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
