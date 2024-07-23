/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:55 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/07 18:15:03 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_words(const char *s, char c)
{
	int		word;

	word = 0;
	while (*s == c && *s != '\0')
		s++;
	while (*s)
	{
		if (*s != c)
		{
			word++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (word);
}

static int	skip(int i, const char *s, char c)
{
	while (s[i] == c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char				**m;
	int					w;
	int					i;
	unsigned int		b;

	if (!s)
		return (NULL);
	m = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (m == NULL)
		return (NULL);
	w = 0;
	i = 0;
	i = skip(i, s, c);
	while (count_words(s, c) != w)
	{
		b = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		m[w] = ft_substr(s, b, i - b);
		i = skip(i, s, c);
		w++;
	}
	m[w] = NULL;
	return (m);
}
