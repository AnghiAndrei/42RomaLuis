/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/22 12:25:31 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*bts_export(t_cmd *cur, char *arg, int i, int i2)
{
	i = get_a(i);
	while (cur->cmd[i] != '\0' && cur->cmd[i] != '+' && cur->cmd[i] != '=')
		i++;
	if (cur->cmd[i] == '+')
	{
		i = i + 2;
		i2 = i;
		return (ft_strjoin(getenv(arg), ft_substr(cur->cmd, i2, i - i2)));
	}
	else if (cur->cmd[i] == '=')
	{
		i = i + 1;
		i2 = i;
		return (ft_substr(cur->cmd, i2, i - i2));
	}
	return (NULL);
}

int	bt_export(t_master *master, t_cmd *cur, int i2)
{
	char	**m2;
	char	**arg;
	char	*extract;

	arg = get_args(cur->cmd, master, cur);
	controll_malloc_matrix(arg);
	if (ft_mlen(arg) > 1 && search_env(master, bts2_export(cur->cmd, 0, 0)) == 0)
	{
		extract = bts2_export(cur, 0, 0);
		m2 = malloc((ft_mlen(master->env) + 2) * sizeof(char *));
		controll_malloc_matrix(m2);
		while (master->env[++i2] != NULL)
			m2[i2] = master->env[i2];
		m2[i2] = ft_strjoin(ft_strjoin(extract, "="), bts_export(cur, extract, 0, 0));
		m2[++i2] = NULL;
		master->env = m2;
	}
	else if (ft_mlen(arg) == 1 && master->print == 1)
		bt_env2(master);
	else
	{
		while (master->env[++i2] != NULL)
		{
			m2[0] = ft_split(master->env[i2], '=');
			if (ft_strncmp(m2[0], extract, ft_strlen(extract) + 1) == 0)
			free_matrix(m2[0]);
		}
	}
	free_matrix(arg);
	free(extract);
	return (1);
}
