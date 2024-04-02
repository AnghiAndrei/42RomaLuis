/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/02 19:40:38 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bts2_export(t_cmd *cur, int *i)
{
	int		i2;

	if (cur->cmd[*i] == '\'' || cur->cmd[*i] == '\"')
	{
		(*i)++;
		i2 = *i;
		while (cur->cmd[*i] != '\0' && cur->cmd[*i] != '\''
			&& cur->cmd[*i] != '\"')
			(*i)++;
	}
	else
	{
		i2 = *i;
		while (cur->cmd[*i] != '\0' && cur->cmd[*i] != ' ')
			(*i)++;
	}
	return (i2);
}

static char	*bts1_export(t_cmd *cur, char *a, int i, t_master *m)
{
	int		i2;
	char	*temp;

	while (cur->cmd[i] != '\0' && cur->cmd[i] != '+' && cur->cmd[i] != '=')
		i++;
	if (cur->cmd[i] == '+')
	{
		i = i + 2;
		i2 = bts2_export(cur, &i);
		return (ft_strjoin12f(get_env(m, a), ft_substr(cur->cmd, i2, i - i2)));
	}
	else if (cur->cmd[i] == '=')
	{
		i = i + 1;
		i2 = bts2_export(cur, &i);
		return (ft_substr(cur->cmd, i2, i - i2));
	}
	temp = malloc(1);
	temp[0] = '\0';
	return (temp);
}

static void	bt_env2(t_master *master, int i)
{
	char	**s;
	char	**mt;

	mt = order(copy_m(master->env), 0, 0, ft_mlen(master->env));
	while (mt[i] != NULL)
	{
		s = ft_split(mt[i], '=');
		if (ft_mlen(s) == 1)
			printf("declare -x %s\n", s[0]);
		else
			printf("declare -x %s=\"%s\"\n", s[0], s[1]);
		free_matrix(s);
		i++;
	}
	free_matrix(mt);
}

static char	**bts3_export(t_master *master, t_cmd *cur, char *e, int i2)
{
	char	**m2;

	m2 = malloc((ft_mlen(master->env) + 2) * sizeof(char *));
	cmmal(m2);
	while (master->env[++i2] != NULL)
		m2[i2] = ft_strjoin(master->env[i2], "\0");
	m2[i2] = ft_strjoin12f(ft_strjoin(e, "="),
			bts1_export(cur, e, get_a(0, cur->cmd), master));
	i2++;
	m2[i2] = NULL;
	free_matrix(master->env);
	return (m2);
}

int	bt_export(t_master *master, t_cmd *cur, int i2)
{
	char	**arg;
	char	**m2;
	char	*e;

	arg = get_args(cur->cmd, master, cur);
	e = extract_mane(cur, 0, 0);
	if (cmmal(arg) != 0 && ft_mlen(arg) > 1 && search_env(master, e) == 0)
		master->env = bts3_export(master, cur, e, i2);
	else if (cmmal(arg) != 0 && ft_mlen(arg) == 1 && master->print == 1)
		bt_env2(master, 0);
	else
	{
		while (master->env[++i2] != NULL)
		{
			m2 = ft_split(master->env[i2], '=');
			if (ft_strncmp(m2[0], e, ft_strlen(e) + 1) == 0
				&& free_norm(master->env[i2]))
				master->env[i2] = ft_strjoin12f(ft_strjoin(e, "="),
						bts1_export(cur, e, get_a(0, cur->cmd), master));
			free_matrix(m2);
		}
	}
	free_matrix(arg);
	free(e);
	return (1);
}
