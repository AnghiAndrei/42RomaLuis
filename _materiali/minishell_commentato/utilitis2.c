/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:17 by aanghi            #+#    #+#             */
/*   Updated: 2024/05/07 14:03:22 by aanghi           ###   ########.fr       */
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
		cm[i] = ft_strjoin(m[i], "\0");
		i++;
	}
	cm[i] = NULL;
	return (cm);
}

int	free_all_2(t_master *master)
{
	free_all(master);
	rl_clear_history();
	free_matrix(master->env);
	close(master->out);
	close(master->in);
	return (0);
}

bool	free_n(char *str)
{
	free(str);
	return (true);
}

char	*get_path(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strjoin(cwd, "\0"));
	else
	{
		perror("Marshal: getcwd() error");
	}
	return (ft_strjoin("\0", "\0"));
}
