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

int	controll_builtins(t_master *master, t_cmd *cur)
{
	if (ft_strncmp(clear_space(cur->cmd), "exit", 5) == 0)
		return (bt_exit(cur->cmd));
	if (ft_strncmp(clear_space(cur->cmd), "env", 4) == 0)
		return (bt_env(master));
	if (ft_strncmp(clear_space(cur->cmd), "export", 7) == 0)
		bt_export(master, cur, -1);
	if (ft_strncmp(clear_space(cur->cmd), "unset", 6) == 0)
		return (1);
	if (ft_strncmp(clear_space(cur->cmd), "echo", 5) == 0)
		return (bt_echo(cur, 0, 0));
	return (0);
}

int	bt_export(t_master *master, t_cmd *cur, int i2)
{
	char	**m2;
	char	**arg;

	arg = get_args(cur->cmd, master, cur);
	controll_malloc_matrix(arg);
	if (ft_mlen(arg) > 1 && search_env(master, arg[1]) == 0)
	{
		m2 = malloc((ft_mlen(master->env) + 2) * sizeof(char *));
		controll_malloc_matrix(m2);
		while (master->env[++i2] != NULL)
			m2[i2] = master->env[i2];
		m2[i2] = ft_strjoin(arg[1], "=");
		m2[++i2] = NULL;
		master->env = m2;
	}
	else if (ft_mlen(arg) == 1 && master->print == 1)
		bt_env2(master);
	free_matrix(arg);
	return (1);
}

int	bt_unset(t_master *master, t_cmd *cur, int i2)
{
	char	**m2;
	char	**s;
	char	**arg;

	arg = get_args(cur->cmd, master, cur);
	controll_malloc_matrix(arg);
	if (ft_mlen(arg) > 1 && search_env(master, arg[1]) == 0)
	{
		m2 = malloc((ft_mlen(master->env)) * sizeof(char *));
		controll_malloc_matrix(m2);
		while (master->env[++i2] != NULL)
		{
			s = ft_split(master->env[i2], '=');
			if (ft_strncmp(s[0], arg[1], ft_strlen(arg[1]) + 1) != 0)
				m2[i2] = master->env[i2];
			free_matrix(s);
		}
		m2[i2] = NULL;
		free_matrix(master->env);
		master->env = m2;
	}
	free_matrix(arg);
	return (1);
}

int	bt_env(t_master *master)
{
	int		i;
	char	**s;
	char	**arg;

	i = 0;
	arg = get_args(cur->cmd, master, cur);
	while (master->env[i] != NULL && master->print == 1)
	{
		s = ft_split(master->env[i], '=');
		if (getenv(s[0]) != NULL)
			printf("%s\n", master->env[i]);
		free_matrix(s);
		i++;
	}
	free_matrix(arg);
	return (1);
}
