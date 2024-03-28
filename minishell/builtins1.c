/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/28 16:13:54 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	free_ret(char *str)
{
	free(str);
	return (true);
}

int	controll_builtins(t_master *master, t_cmd *cur)
{
	char	*str;

	str = clear_space(cur->cmd);
	if (ft_strncmp(str, "exit", 5) == 0 && free_ret(str))
		return (bt_exit(master, cur->cmd, 0, 0));
	if (ft_strncmp(str, "env", 4) == 0 && free_ret(str))
		return (bt_env(master, cur));
	if (ft_strncmp(str, "export", 7) == 0 && free_ret(str))
		return (bt_export(master, cur, -1));
	if (ft_strncmp(str, "unset", 6) == 0 && free_ret(str))
		return (1);
	if (ft_strncmp(str, "echo", 5) == 0 && free_ret(str))
		return (bt_echo(master, cur, 0, 0));
	if (ft_strncmp(str, "cd", 3) == 0 && free_ret(str))
		return (1);
	if (ft_strncmp(str, "pwd", 4) == 0 && free_ret(str))
		return (bt_pwd());
	return (0);
}

int	bt_unset(t_master *master, t_cmd *cur, int i2, char *b)
{
	char	**arg;
	char	**m2;
	char	**s;
	int		i;

	i = -1;
	arg = get_args(cur->cmd, master, cur);
	if (cmmal(arg) == 1 && ft_mlen(arg) > 1 && search_env(master, b) != 0)
	{
		m2 = malloc((ft_mlen(master->env)) * sizeof(char *));
		while (master->env[++i2] != NULL && cmmal(arg))
		{
			s = ft_split(master->env[i2], '=');
			if (cmmal(s) == 1 && ft_strncmp(s[0], b, ft_strlen(b) + 1) != 0)
				m2[++i] = ft_strjoin(master->env[i2], "");
			free_matrix(s);
		}
		m2[i] = NULL;
		free_matrix(master->env);
		master->env = m2;
		free_matrix(m2);
		free_matrix(arg);
	}
	free(b);
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
