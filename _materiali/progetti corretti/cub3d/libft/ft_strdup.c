/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everolla <everolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:48:32 by pcoletta          #+#    #+#             */
/*   Updated: 2024/03/13 18:17:15 by everolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	char	*dup;
	size_t	i;

	i = ft_strlen(s1) + 1;
	dup = (char *) malloc(sizeof(char) * i);
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s1, i);
	return (dup);
}
