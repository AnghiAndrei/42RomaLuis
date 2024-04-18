/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoletta <pcoletta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:46:43 by pcoletta          #+#    #+#             */
/*   Updated: 2022/01/10 12:46:46 by pcoletta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;
	unsigned char	cc;

	i = 0;
	cs = (unsigned char *) s;
	cc = (unsigned char) c;
	while (i < n)
	{
		if (cs[i] == cc)
			return ((void *) s + i);
		i++;
	}
	return (NULL);
}
