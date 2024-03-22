/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:57:23 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/09 17:57:34 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	i2;
	size_t	lenn;

	if (haystack == NULL && len == 0)
		return (NULL);
	lenn = ft_strlen((char *)needle);
	if (lenn == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		i2 = 0;
		while (i + i2 < len && haystack[i + i2] == needle[i2]
			&& needle[i2] != '\0')
			i2++;
		if (needle[i2] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
