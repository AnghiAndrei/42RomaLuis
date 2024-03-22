/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:21 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/09 16:17:36 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p1;
	size_t			i;

	i = 0;
	p1 = (unsigned char *)s;
	while (i < n)
	{
		if (*p1 == (unsigned char)c)
			return ((void *)p1);
		p1++;
		i++;
	}
	return (NULL);
}
