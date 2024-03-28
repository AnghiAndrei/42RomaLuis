/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:17 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/28 16:13:54 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_m(char **m)
{
	char	**cm;
	int		i;

	i = 0;
	cm = malloc((ft_mlen(m) + 1) * sizeof(char *));
	while (m[i] != NULL)
	{
		cm[i] = ft_strjoin(m[i], "");
		i++;
	}
	cm[i] = NULL;
	return (cm);
}

void	free_all_steoridi(t_master *master)
{
	free_all(master);
	rl_clear_history();
	free_matrix(master->env);
}
