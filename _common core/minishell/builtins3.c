/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/05 02:29:20 by aanghi           ###   ########.fr       */
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

int	bt_export(t_master *mast, t_cmd *cur, t_data2 d)
{
	char	**m2;

	d.arg = get_args(cur->cmd, mast, cur);
	if (cmmal(d.arg) != 0 && ft_mlen(d.arg) > 1 && search_env(mast, d.t1) == 0)
		mast->env = bts3_export(mast, cur, d.t1, d.i);
	else if (cmmal(d.arg) != 0 && ft_mlen(d.arg) == 1 && mast->print == 1)
		bt_env2(mast, 0);
	else
	{
		while (mast->env[++d.i] != NULL)
		{
			m2 = ft_split(mast->env[d.i], '=');
			if (ft_strncmp(m2[0], d.t1, ft_strlen(d.t1) + 1) == 0)
			{
				d.t2 = ft_strjoin12f(ft_strjoin(d.t1, "="),
						bts1_export(cur, d.t1, get_a(0, cur->cmd), mast));
				free(mast->env[d.i]);
				mast->env[d.i] = ft_strjoin1f(d.t2, "\0");
			}
			free_matrix(m2);
		}
	}
	free_matrix(d.arg);
	free(d.t1);
	return (1);
}
