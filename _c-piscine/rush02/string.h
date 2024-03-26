/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:33:51 by apuddu            #+#    #+#             */
/*   Updated: 2023/11/12 20:33:52 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include "string_a.h"
# include <stdlib.h>
# include <unistd.h>
// deletes trailing whitespace of a string (may be in-place)
char	*strip(char *str)
{
	int	i;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		str[i] = 0;
		i--;
	}
	return (str);
}

int	streq(char *a, char *b)
{
	while (*a == *b && *a)
	{
		a++;
		b++;
	}
	return (*a == *b);
}

// mallocs a copy of str
char	*ft_strcpy(char *str)
{
	int		sz;
	char	*copy;
	char	*it;

	sz = ft_strlen(str);
	copy = (char *)malloc(sz);
	it = copy;
	while (*str)
	{
		*it = *str;
		it++;
		str++;
	}
	*it = 0;
	return (copy);
}

#endif