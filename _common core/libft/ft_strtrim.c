/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:28:35 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/09 17:28:44 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		ls1;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	ls1 = ft_strlen((char *)s1);
	start = 0;
	end = ls1 - 1;
	while (start < ls1 && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	trimmed_str = (char *)malloc((end - start + 2));
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, s1 + start, end - start + 2);
	return (trimmed_str);
}
