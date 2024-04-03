/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/03 17:23:13 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_exit(t_master *master, char *cmd, int i, int i2)
{
	char	*str;

	i2 = i;
	while (cmd[i] != ' ' && cmd[i] != '\0' && ft_isdigit(cmd[i]))
		i++;
	rl_clear_history();
	if (cmd[i] == ' ' || cmd[i] == '\0')
	{
		printf("02: Sayōnara, darling\n");
		str = ft_substr(cmd, i2, i - i2);
		i = ft_atoi(str);
		free(str);
		free_all(master);
		free_matrix(master->env);
		exit(i);
	}
	else
	{
		free_all(master);
		free_matrix(master->env);
		write(2, "Marshal: Requested numerical value\n", 35);
		g_code_exit = 2;
		exit(2);
	}
	return (1);
}

int	bt_echo(t_master *master, t_cmd *cur, int i, int n)
{
	char	**arg;
	char	*cstr;
	char	*cstr2;

	arg = get_args(cur->cmd, master, cur);
	while (arg[++i] != NULL)
	{
		cstr = clear_space(arg[i]);
		cstr2 = clear_space(arg[i + 1]);
		if (ft_strncmp(cstr, "-n", 3) == 0)
			n++;
		else
		{
			printf("%s", arg[i]);
			if (arg[i + 1] != NULL && ft_strncmp(cstr2, "-n", 3) != 0)
				printf(" ");
		}
		free(cstr);
		free(cstr2);
	}
	if (n == 0)
		printf("\n");
	free_matrix(arg);
	return (1);
}

int	bt_cd(t_master *master, t_cmd *cur, char *home, char **arg)
{
	free(cur->cmd);
	cur->cmd = ft_strjoin2f("export OLDPWD=", get_path());
	bt_export(master, cur, (t_data2){NULL, extr_m(cur, 0, 0), NULL, -1});
	if (cmmal(arg) == 1 && ft_mlen(arg) == 2)
		chdir(arg[1]);
	else if (cmmal(arg) == 1 && ft_mlen(arg) == 1)
		chdir(home);
	free(cur->cmd);
	cur->cmd = ft_strjoin2f("export PWD=", get_path());
	bt_export(master, cur, (t_data2){NULL, extr_m(cur, 0, 0), NULL, -1});
	free(cur->cmd);
	cur->cmd = ft_strjoin("cd", "\0");
	free_matrix(arg);
	return (free(home), 1);
}

int	bt_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("Marshal: getcwd() error");
	}
	return (1);
}
