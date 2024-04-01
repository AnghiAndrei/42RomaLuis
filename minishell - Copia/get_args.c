/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:55 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/28 02:43:16 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*clear_cmd(char *s, t_master *master, t_cmd *cmd)
{
	t_data		d;

	s = trim_cmd(s, master, cmd, 0);
	d.i = 0;
	d.i2 = 0;
	d.quote = 0;
	d.dquote = 0;
	d.env_var = NULL;
	d.env_name = NULL;
	s = expander(master, cmd, d);
	d.i = 0;
	d.i2 = 0;
	s = wildcard(master, cmd, -1);
	return (s);
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
		i++;
	}
	return (word);
}

char	**get_args(char *s, t_master *master, t_cmd *cmd)
{
	char				**m;
	int					w;
	int					i;

	s = clear_cmd(s, master, cmd);
	m = (char **)malloc((count_arg(s) + 1) * sizeof(char *));
	cmmal(m);
	w = 0;
	i = skip(0, s);
	while (count_arg(s) != w)
		gu4(&i, s, &w, m);
	m[w] = NULL;
	return (redirect(m));
}
