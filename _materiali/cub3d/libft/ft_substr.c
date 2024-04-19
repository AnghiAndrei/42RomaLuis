/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everolla <everolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:50:03 by pcoletta          #+#    #+#             */
/*   Updated: 2024/03/13 18:15:57 by everolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;
	size_t			size;

	if (s == NULL)
		return (NULL);
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	size = ft_strlen(s);
	i = 0;
	while (i + start < size && s[i + start] != '\0' && i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
