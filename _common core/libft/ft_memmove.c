/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:35:59 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/09 16:36:11 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (unsigned char *)dest;
	p2 = (const unsigned char *)src;
	if (!dest && !src && n > 0)
		return (NULL);
	i = 0;
	if (p2 < p1)
	{
		while (n--)
			p1[n] = p2[n];
	}
	else
	{
		while (n != 0)
		{
			p1[i] = p2[i];
			i++;
			n--;
		}
	}
	return (dest);
}
