/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoletta <pcoletta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:46:58 by pcoletta          #+#    #+#             */
/*   Updated: 2022/01/10 14:51:15 by pcoletta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;

	cdst = (unsigned char *) dst;
	csrc = (unsigned char *) src;
	if (cdst == NULL && csrc == NULL)
		return (NULL);
	while (n--)
		cdst[n] = csrc[n];
	return (dst);
}
