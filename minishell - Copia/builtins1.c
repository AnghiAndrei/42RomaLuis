/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/25 17:10:28 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	controll_builtins(t_master *master, t_cmd *cur)
{
	if (ft_strncmp(clear_space(cur->cmd), "exit", 5) == 0)
		return (bt_exit(cur->cmd));
	if (ft_strncmp(clear_space(cur->cmd), "env", 4) == 0)
		return (bt_env(master, cur));
	if (ft_strncmp(clear_space(cur->cmd), "export", 7) == 0)
		return (bt_export(master, cur, -1));
	if (ft_strncmp(clear_space(cur->cmd), "unset", 6) == 0)
		return (1);
	if (ft_strncmp(clear_space(cur->cmd), "echo", 5) == 0)
		return (bt_echo(master, cur, 0, 0));
	if (ft_strncmp(clear_space(cur->cmd), "cd", 3) == 0)
		return (1);
	if (ft_strncmp(clear_space(cur->cmd), "pwd", 4) == 0)
		return (bt_pwd());
	return (0);
}

int	bt_unset(t_master *master, t_cmd *cur, int i2, char *str)
{
	char	**arg;
	char	**m2;
	char	**s;
	int		i;

	arg = get_args(cur->cmd, master, cur);
	i = -1;
	if (cmmal(arg) == 1 && ft_mlen(arg) > 1 && search_env(master, str) != 0)
	{
		m2 = malloc((ft_mlen(master->env) + 1) * sizeof(char *));
		while (master->env[++i2] != NULL && cmmal(arg))
		{
			s = ft_split(master->env[i2], '=');
			if (ft_strncmp(s[0], str, ft_strlen(str) + 1) != 0)
				m2[++i] = master->env[i2];
			free_matrix(s);
		}
		m2[++i] = NULL;
		free_matrix(master->env);
		master->env = m2;
	}
	free_matrix(arg);
	free(str);
	return (1);
}

int	bt_env(t_master *master, t_cmd *cur)
{
	int		i;
	char	**s;
	char	**arg;

	i = 0;
	arg = get_args(cur->cmd, master, cur);
	while (master->env[i] != NULL && master->print == 1)
	{
		s = ft_split(master->env[i], '=');
		if (get_env(master, s[0]) != NULL)
			printf("%s\n", master->env[i]);
		free_matrix(s);
		i++;
	}
	free_matrix(arg);
	return (1);
}
