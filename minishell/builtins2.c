/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/25 17:11:02 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	bt_echo(t_master *master, t_cmd *cur, int i, int n)
{
	char	**arg;

	arg = get_args(cur->cmd, master, cur);
	while (arg[++i] != NULL)
	{
		if (ft_strncmp(clear_space(arg[i]), "-n", 3) == 0 && n++ && i++)
			continue ;
		write(1, clear_space(arg[i]), ft_strlen(clear_space(arg[i])));
		if (arg[i + 1] != NULL)
			write(1, " ", 1);
	}
	if (n == 0)
		printf("\n");
	free_matrix(arg);
	return (1);
}

int	bt_cd(t_master *master, t_cmd *cur, int i)
{
	i = get_a(0, cur->cmd);
	while (master->env[i] != NULL)
		i++;
	return (1);
}

int	bt_pwd(t_master *master, t_cmd *cur)
{
	char	cwd[1024];
	char	**arg;

	arg = get_args(cur->cmd, master, cur);
	controll_malloc_matrix(arg);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
	{
        perror("getcwd() error");
	}
	free_matrix(arg);
	return (1);
}
