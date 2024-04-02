/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:55:20 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/02 14:59:27 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip(int i, char *s)
{
	if (s == NULL)
		return (i);
	while (s[i] != '\0')
	{
		if (s[i] == '\t' || s[i] == ' ')
		{
			i++;
			continue ;
		}
		break ;
	}
	return (i);
}

void	spik_duote(int *i, char *str, char c)
{
	if (str[*i] != c)
		return ;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	(*i)++;
}

int	count_pipe(char *str, char c)
{
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	while (str[i2] != '\0')
	{
		spik_duote(&i2, str, '\'');
		spik_duote(&i2, str, '\"');
		if (str[i2] == c && str[i2 + 1] == c)
			i2 += 2;
		if (str[i2] == c && str[i2 + 1] != c)
			i += 1;
		i2++;
	}
	return (i);
}

void	free_all(t_master *master)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = master->lcmd;
	while (cur->next != NULL)
	{
		free(cur->cmd);
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(cur->cmd);
	free(cur);
	master->lcmd = NULL;
	free(master->input);
	master->ncmd = 0;
}

char	*program_name(char *command, char *path)
{
	char	**c_c;
	char	**path_c;
	char	*temp;
	int		i;

	c_c = ft_split((const char *)command, ' ');
	path_c = ft_split((const char *)path, ':');
	if (access(c_c[0], R_OK) == 0)
		return (c_c[0]);
	i = 0;
	while (path_c[i] != NULL)
	{
		temp = ft_strjoin1f(ft_strjoin(path_c[i], "/"), c_c[0]);
		if (access(temp, R_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	write(2, "02: What command did you give me, darling\n", 42);
	exit(EXIT_FAILURE);
	return (NULL);
}
