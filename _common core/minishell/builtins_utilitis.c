/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utilitis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/05 02:03:11 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_env(t_master *master, char *rule)
{
	char	**s;
	int		i;

	i = 0;
	while (master->env[i] != NULL)
	{
		s = ft_split(master->env[i], '=');
		cmmal(s);
		if (ft_mlen(s) >= 1
			&& ft_strncmp(s[0], rule, ft_strlen(rule) + 1) == 0)
			return (free_matrix(s), 1);
		free_matrix(s);
		i++;
	}
	return (0);
}

char	*extr_m(t_cmd *cur, int i, int i2)
{
	i = get_a(0, cur->cmd);
	i2 = i;
	while (cur->cmd[i] != '\0' && cur->cmd[i] != '+' && cur->cmd[i] != '='
		&& cur->cmd[i] != ' ')
		i++;
	return (ft_substr(cur->cmd, i2, i - i2));
}

int	get_a(int i, char *cmd)
{
	i = skip(i, cmd);
	while (cmd[i] != ' ' && cmd[i] != '\0')
		i++;
	i = skip(i, cmd);
	return (i);
}

char	*get_env(t_master *master, char *env)
{
	char	**s;
	char	*d;
	int		i;

	i = 0;
	while (master->env[i] != NULL)
	{
		s = ft_split(master->env[i], '=');
		if (ft_mlen(master->env) >= 2
			&& ft_strncmp(s[0], env, ft_strlen(env) + 1) == 0)
		{
			d = ft_strjoin(s[1], "\0");
			free_matrix(s);
			return (d);
		}
		free_matrix(s);
		i++;
	}
	d = malloc(1);
	d[0] = '\0';
	return (d);
}

char	**order(char **mt, int i, int i2, int len)
{
	char	*temp;

	while (i < len - 1)
	{
		i2 = 0;
		while (i2 < len - i - 1)
		{
			if (ft_strncmp(mt[i2], mt[i2 + 1], ft_strlen(mt[i2 + 1])) > 0)
			{
				temp = mt[i2];
				mt[i2] = mt[i2 + 1];
				mt[i2 + 1] = temp;
			}
			i2++;
		}
		i++;
	}
	return (mt);
}
