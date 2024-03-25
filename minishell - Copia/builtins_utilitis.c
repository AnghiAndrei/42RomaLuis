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
	char	**s;

	i = 0;
	while (master->env[i] != NULL)
	{
		s = ft_split(master->env[i], '=');
		if (ft_strncmp(s[0], rule, ft_strlen(rule) + 1) == 0)
			return (1);
		i++;
		free_matrix(s);
	}
	return (0);
}

char	*extract_mane(t_cmd *cur, int i, int i2)
{
	i = get_a(cur->cmd);
	i2 = i;
	while (cur->cmd[i] != '\0' && cur->cmd[i] != '+' && cur->cmd[i] != '=')
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
