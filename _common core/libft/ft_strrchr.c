/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:02:14 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/09 18:02:19 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i != 0 && str[i] != c)
		i--;
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	else
		return (NULL);
}
