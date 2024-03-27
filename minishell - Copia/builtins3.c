/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/25 13:30:47 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*bts1_export(t_cmd *cur, char *arg, int i, t_master *master)
{
	int		i2;

	i = get_a(0, cur->cmd);
	while (cur->cmd[i] != '\0' && cur->cmd[i] != '+' && cur->cmd[i] != '=')
		i++;
	if (cur->cmd[i] == '+')
	{
		i = i + 2;
		i2 = i;
		while (cur->cmd[i] != '\0' && cur->cmd[i] != ' ')
			i++;
		if (cur->cmd[i] == ' ')
			i--;
		return (ft_strjoin(get_env(master, arg), ft_substr(cur->cmd, i2, i - i2)));
	}
	else if (cur->cmd[i] == '=')
	{
		i = i + 1;
		i2 = i;
		while (cur->cmd[i] != '\0' && cur->cmd[i] != ' ')
			i++;
		if (cur->cmd[i] == ' ')
			i--;
		return (ft_substr(cur->cmd, i2, i2 - i));
	}
	return (NULL);
}

static	char	**order(char **mt)
{
	char	*temp;
	int		i;

	i = 0;
	while (mt[i + 1] != NULL)
	{
		if (ft_strncmp(mt[i + 1], mt[i], ft_strlen(mt[i])) > 0)
		{
			i = 0;
			temp = mt[i + 1];
			mt[i + 1] = mt[i];
			mt[i] = temp;
		}
		i++;
	}
	return (mt);
}

static void	bt_env2(t_master *master, int i)
{
	char	**s;
	char	**mt;

	mt = order(copy_m(master->env));
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

int	bt_export(t_master *master, t_cmd *cur, int i2)
{
	char	**m2;
	char	**arg;
	char	*extract;

	arg = get_args(cur->cmd, master, cur);
	cmmal(arg);
	extract = extract_mane(cur, 0, 0);
	if (ft_mlen(arg) > 1 && search_env(master, extract) == 0)
	{
		m2 = malloc((ft_mlen(master->env) + 2) * sizeof(char *));
		cmmal(m2);
		while (master->env[++i2] != NULL)
			m2[i2] = master->env[i2];
		m2[i2] = ft_strjoin(ft_strjoin(extract, "="), bts1_export(cur, extract, 0, 0));
		if (m2[i2] == NULL)
			m2[i2] = ft_strjoin(extract, "=");
		m2[++i2] = NULL;
		master->env = m2;
	}
	else if (ft_mlen(arg) == 1 && master->print == 1)
		bt_env2(master, 0);
	else
	{
		while (master->env[++i2] != NULL)
		{
			m2 = ft_split(master->env[i2], '=');
			if (ft_strncmp(m2[0], extract, ft_strlen(extract) + 1) == 0)
				master->env[i2] = ft_strjoin(ft_strjoin(extract, "="), bts1_export(cur, extract, 0, 0));
			free_matrix(m2);
		}
	}
	free_matrix(arg);
	free(extract);
	return (1);
}
