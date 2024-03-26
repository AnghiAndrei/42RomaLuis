/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:17:22 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/06 11:28:19 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	sup_strcmp(char *s1, char *s2);

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (sup_strcmp(s1, s2));
}

int	sup_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s2 != '\0')
			s2++;
		s1++;
	}
	while (*s2 != '\0')
	{
		if (*s2 != *s1)
			return (*s1 - *s2);
		if (*s1 != '\0')
			s1++;
		s2++;
	}
	return (0);
}
