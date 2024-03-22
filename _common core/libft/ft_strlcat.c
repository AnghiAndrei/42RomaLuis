/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <aanghi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:26:12 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/17 14:25:41 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	i2;

	if (size == 0)
		return (ft_strlen((char *)src));
	i = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	if (i >= size)
		return (i + ft_strlen((char *)src));
	i2 = 0;
	while (src[i2] != '\0' && i2 + i < size - 1)
	{
		dest[i + i2] = src[i2];
		i2++;
	}
	dest[i + i2] = '\0';
	return (i + ft_strlen((char *)src));
}
