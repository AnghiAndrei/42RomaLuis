/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:17 by aanghi            #+#    #+#             */
/*   Updated: 2024/05/07 14:18:52 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_start(t_master *master, char **env)
{
	master->ncmd = 0;
	master->env = copy_m(env);
	master->lcmd = NULL;
	master->out = dup(STDOUT_FILENO);
	master->in = dup(STDIN_FILENO);
	return (0);
}

char	*clear_space(char *str)
{
	int		i;
	int		i2;

	if (str == NULL)
		return (NULL);
	i = skip(0, str);
	i2 = i;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return (ft_substr(str, i2, i - i2));
}

int	ft_mlen(char **m)
{
	int		i;

	i = 0;
	while (m[i] != NULL)
		i++;
	return (i);
}

int	free_matrix(char **m)
{
	int		i;

	if (m == NULL)
		return (0);
	if (m != NULL)
	{
		i = 0;
		while (m[i] != NULL)
		{
			if (m[i] != NULL)
			{
				free(m[i]);
				m[i] = NULL;
			}
			i++;
		}
		free(m);
		m = NULL;
	}
	return (0);
}