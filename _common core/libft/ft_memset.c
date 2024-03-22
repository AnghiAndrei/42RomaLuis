/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:44:08 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/09 16:44:19 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p1;
	size_t			i;

	i = 0;
	p1 = (unsigned char *)b;
	while (i != len)
	{
		p1[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
