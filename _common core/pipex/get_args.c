/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:55 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/02 16:12:21 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	skip(int i, char *s)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

static int	count_arg(char *s)
{
	int		word;
	int		i;

	word = 0;
	i = skip(0, s);
	while (s[i])
	{
		if (s[i] == '\'')
			gu1(&word, s, &i, '\'');
		else if (s[i] == '\'')
			gu1(&word, s, &i, '\"');
		else if (s[i] != ' ')
		{
			word++;
			while (s[i] != '\0' && s[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (word);
}

char	**get_args(char *s)
{
	char				**m;
	int					w;
	int					i;

	m = (char **)malloc((count_arg(s) + 1) * sizeof(char *));
	controll2(m);
	w = 0;
	i = skip(0, s);
	while (count_arg(s) != w)
	{
		if (s[i] == '\'')
			m[w] = gu2(&i, s, '\'');
		else if (s[i] == '\"')
			m[w] = gu2(&i, s, '\"');
		else if (s[i] != ' ')
			m[w] = gu3(&i, s);
		else
			i++;
		i = skip(i, s);
		w++;
	}
	m[w] = NULL;
	return (m);
}
