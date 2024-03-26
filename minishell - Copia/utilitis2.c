/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:17 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/21 17:32:55 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	**copy_m(char **m)
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
	return (cm);
}
