/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:55 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/07 14:45:00 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	gu1(int *word, char *s, int *i, char ch)
{
	int		c;

	(*i)++;
	c = *i;
	while (s[*i] != '\0' && s[*i] != ch)
		(*i)++;
	if (s[*i] == '\0')
		*i = c;
	else
		(*word)++;
}

char	*gu2(int *i, char *s, char ch)
{
	int		c;

	(*i)++;
	c = *i;
	while (s[*i] != '\0' && s[*i] != ch)
		(*i)++;
	if (s[*i] == '\0')
		return (ft_substr(s, c - 1, *i - c + 1));
	else
		return (ft_substr(s, c, *i - c));
}

char	*gu3(int *i, char *s)
{
	int		b;

	b = *i;
	while (s[*i] != '\0' && s[*i] != ' ')
		(*i)++;
	return (ft_substr(s, b, *i - b));
}
