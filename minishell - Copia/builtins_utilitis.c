/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utilitis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:13 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/21 17:08:49 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_env(t_master *master, char *rule)
{
	int		i;

	i = 0;
	while (master->env[i] != NULL)
	{
		if (ft_strncmp(master->env[i], ft_strjoin(rule, "="),
				ft_strlen(rule) + 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	get_a(int i, char *cmd)
{
	i = skip(i, cmd);
	while (cmd[i] != ' ' && cmd[i] != '\0')
		i++;
	i = skip(i, cmd);
	return (i);
}

void	bt_env2(t_master *master)
{
	int		i;

	i = 0;
	while (master->env[i] != NULL)
	{
		printf("declare -x \"%s\"\n", master->env[i]);
		i++;
	}
}
