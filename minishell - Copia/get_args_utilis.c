/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:55 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/18 16:58:49 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gu1(int *word, char *s, int *i, char ch)
{
	(*i)++;
	while (s[*i] != '\0' && s[*i] != ch)
		(*i)++;
	(*word)++;
}

char	*gu2(int *i, char *s, char ch)
{
	int		c;

	(*i)++;
	c = *i;
	while (s[*i] != '\0' && s[*i] != ch)
		(*i)++;
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

void	gu4(int *i, char *s, int *w, char **m)
{
	if (s[*i] == '\'')
		m[*w] = gu2(i, s, '\'');
	else if (s[*i] == '\"')
		m[*w] = gu2(i, s, '\"');
	else if (s[*i] != ' ')
		m[*w] = gu3(i, s);
	else
		(*i)++;
	if (s[*i] == '\'')
		(*i)++;
	else if (s[*i] == '\"')
		(*i)++;
	*i = skip(*i, s);
	(*w)++;
}

char	*trim_cmd(char *str, t_master *master, t_cmd *cmd, int i)
{
	char	**path_c;
	char	*join;

	path_c = ft_split((const char *)master->path, ':');
	join = ft_strjoin(path_c[i], "/");
	while (path_c[i] != NULL)
	{
		if (ft_strncmp(str, join, ft_strlen(join)) == 0)
		{
			cmd->cmd = cmd->cmd + ft_strlen(join);
		}
		free(join);
		join = ft_strjoin(path_c[i++], "/");
	}
	return (cmd->cmd);
}
