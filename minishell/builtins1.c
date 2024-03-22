/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/21 17:30:55 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	controll_builtins(t_master *master, t_cmd *cur)
{
	char	*str;

	str = clear_space(cur->cmd);
	if (ft_strncmp(str, "exit", 5) == 0)
		return (bt_exit(cur->cmd));
	if (ft_strncmp(str, "env", 4) == 0)
		return (bt_env(master));
	if (ft_strncmp(str, "export", 7) == 0)
		return (1);
	if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	free(str);
	return (0);
}

int	bt_unset(t_master *master, t_cmd *cur, int i2, int i)
{
	char	**m2;
	char	**arg;

	arg = get_args(cur->cmd, master, cur);
	controll_malloc_matrix(arg);
	if (ft_mlen(arg) > 1 && search_env(master, arg[1]) == 0)
	{
		m2 = malloc((ft_mlen(master->env)) * sizeof(char *));
		controll_malloc_matrix(m2);
		while (master->env[++i2] != NULL)
		{
			if (ft_strncmp(master->env[i2], arg[1], ft_strlen(arg[1]) + 1) != 0)
				m2[i2] = master->env[i2];
		}
		m2[i2] = NULL;
		master->env = m2;
	}
	while (arg[++i] != NULL)
		free(arg[i]);
	free(arg);
	return (1);
}

int	bt_export(t_master *master, t_cmd *cur, int i2, int i)
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
	else if (ft_mlen(arg) == 1)
		bt_env2(master);
	while (arg[++i] != NULL)
		free(arg[i]);
	free(arg);
	return (1);
}

int	bt_env(t_master *master)
{
	int		i;
	int		i2;
	char	**s;

	i = 0;
	while (master->env[i] != NULL)
	{
		s = ft_split(master->env[i], '=');
		if (getenv(s[0]) != NULL)
			printf("%s\n", master->env[i]);
		i2 = -1;
		while (s[++i2] != NULL)
			free(s[i2]);
		free(s);
		i++;
	}
	return (1);
}

int	bt_exit(char *cmd)
{
	int		i;
	int		i2;

	i = get_a(0, cmd);
	i2 = i;
	while (cmd[i] != ' ' && cmd[i] != '\0' && ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] == ' ' || cmd[i] == '\0')
	{
		printf("02: Sayōnara, darling\n");
		exit(ft_atoi(ft_substr(cmd, i2, i - i2)));
	}
	else
	{
		perror("Marshal: Requested numerical value");
		exit(EXIT_FAILURE);
	}
	return (1);
}
