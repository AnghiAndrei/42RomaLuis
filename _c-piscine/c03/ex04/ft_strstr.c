/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:18:17 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/02 17:18:21 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*to_find == '\0')
		return (str);
	while (1)
	{
		if (to_find[j] == '\0')
			return (&str[i - j]);
		if (str[i] == to_find[j])
			j++;
		else
			j = 0;
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (0);
}
