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

static char	*bts1_export(t_cmd *cur, char *arg, int i, int i2)
{
	i = get_a(0, cur->cmd);
	while (cur->cmd[i] != '\0' && cur->cmd[i] != '+' && cur->cmd[i] != '=')
		i++;
	if (cur->cmd[i] == '+')
	{
		i = i + 2;
		i2 = i;
		while (cur->cmd[i] != '\0' && cur->cmd[i] != ' ')
			i++;
		return (ft_strjoin(getenv(arg), ft_substr(cur->cmd, i2, i - i2)));
	}
	else if (cur->cmd[i] == '=')
	{
		i = i + 1;
		i2 = i;
		while (cur->cmd[i] != '\0' && cur->cmd[i] != ' ')
			i++;
		return (ft_substr(cur->cmd, i2, i2 - i));
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
	extract = extract_mane(cur, 0, 0);
	if (ft_mlen(arg) > 1 && search_env(master, extract) == 0)
	{
		printf("RIMALLOC\n");
		m2 = malloc((ft_mlen(master->env) + 2) * sizeof(char *));
		controll_malloc_matrix(m2);
		while (master->env[++i2] != NULL)
			m2[i2] = master->env[i2];
		m2[i2] = ft_strjoin(ft_strjoin(extract, "="), bts1_export(cur, extract, 0, 0));
		if (m2[i2] == NULL)
			m2[i2] = ft_strjoin(extract, "=");
		m2[++i2] = NULL;
		master->env = m2;
	}
	else if (ft_mlen(arg) == 1 && master->print == 1)
		bt_env2(master);
	else
	{
		printf("REINSERIMENTO\n");
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
