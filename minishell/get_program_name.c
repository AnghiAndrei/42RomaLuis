/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:29:54 by aanghi            #+#    #+#             */
/*   Updated: 2024/05/09 14:52:18 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**clean_m(char **m, int i, int i2, int i3)
{
	char	**m2;

	m2 = malloc((i + 1) * sizeof(char *));
	cmmal(m2);
	while (m[i2] != NULL)
	{
		if (ft_strncmp(m[i2], " ", 2) != 0)
			m2[i3++] = ft_strjoin(m[i2], "\0");
		i2++;
	}
	m2[i3] = NULL;
	free_matrix(m);
	return (m2);
}

static void	mod_m(char **m, int i)
{
	free(m[i]);
	free(m[i + 1]);
	m[i] = malloc(2);
	m[i][0] = ' ';
	m[i][1] = '\0';
	m[i + 1] = malloc(2);
	m[i + 1][0] = ' ';
	m[i + 1][1] = '\0';
}

static char	**clear_red(char **m)
{
	int	i;

	i = 0;
	while (m[i] != NULL)
	{
		if (ft_strncmp(m[i], ">", 2) == 0 && m[i + 1] != NULL)
			mod_m(m, i);
		else if (ft_strncmp(m[i], ">>", 3) == 0 && m[i + 1] != NULL)
			mod_m(m, i);
		else if (ft_strncmp(m[i], "<", 2) == 0 && m[i + 1] != NULL)
			mod_m(m, i);
		else if (ft_strncmp(m[i], "<<", 3) == 0 && m[i + 1] != NULL)
			mod_m(m, i);
		i++;
	}
	return (clean_m(m, i, 0, 0));
}


char	*program_name(char *command, char *path)
{
	char	**c_c;
	char	**path_c;
	char	*temp;
	int		i;

	c_c = clear_red(ft_split((const char *)command, ' '));
	if (c_c[0]==NULL)
		return (NULL);
	path_c = ft_split((const char *)path, ':');
	free(path);
	temp = ft_strjoin(c_c[0], "\0");
	if (access(c_c[0], X_OK) == 0 && free_matrix(c_c) == 0
		&& free_matrix(path_c) == 0)
		return (temp);
	free(temp);
	i = -1;
	while (path_c[++i] != NULL)
	{
		temp = ft_strjoin1f(ft_strjoin(path_c[i], "/"), c_c[0]);
		if (access(temp, X_OK) == 0 && free_matrix(c_c) == 0
			&& free_matrix(path_c) == 0)
			return (temp);
		free(temp);
	}
	return (free_matrix(c_c), free_matrix(path_c), NULL);
}
