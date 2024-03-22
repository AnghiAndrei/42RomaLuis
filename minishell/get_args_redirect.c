/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:21:10 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/22 12:26:12 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**clean_m(char **m, int i, int i2, int i3)
{
	char	**m2;

	m2 = malloc((i + 1) * sizeof(char *));
	controll_malloc_matrix(m2);
	while (m[i2] != NULL)
	{
		if (ft_strncmp(m[i2], " ", 2) != 0)
			m2[i3++] = m[i2];
		else
			free(m[i2]);
		i2++;
	}
	free(m);
	m2[i3] = NULL;
	return (m2);
}

static void	mod_m(char **m, int i, int op)
{
	if (op == 1)
		dup2(controll_file(m[i + 1], 3), STDOUT_FILENO);
	else if (op == 2)
		dup2(controll_file(m[i + 1], 4), STDOUT_FILENO);
	else if (op == 3)
		dup2(controll_file(m[i + 1], 1), STDIN_FILENO);
	else if (op == 4)
		here_doc(m[i + 1]);
	free(m[i]);
	free(m[i + 1]);
	m[i] = malloc(2);
	m[i][0] = ' ';
	m[i][1] = '\0';
	m[i + 1] = malloc(2);
	m[i + 1][0] = ' ';
	m[i + 1][1] = '\0';
}

char	**redirect(char **m)
{
	int	i;

	i = 0;
	while (m[i] != NULL)
	{
		if (ft_strncmp(m[i], ">", 2) == 0 && m[i + 1] != NULL)
			mod_m(m, i, 1);
		else if (ft_strncmp(m[i], ">>", 3) == 0 && m[i + 1] != NULL)
			mod_m(m, i, 2);
		else if (ft_strncmp(m[i], "<", 2) == 0 && m[i + 1] != NULL)
			mod_m(m, i, 3);
		else if (ft_strncmp(m[i], "<<", 3) == 0 && m[i + 1] != NULL)
			mod_m(m, i, 4);
		i++;
	}
	return (clean_m(m, i, 0, 0));
}
