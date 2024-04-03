/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:55 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/02 12:04:54 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_file(t_data d)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(get_path());
	if (dir == NULL)
	{
		perror("Marshal: Opendir error");
		exit(EXIT_FAILURE);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			if (ft_strncmp(entry->d_name, ".", 2) != 0
				&& ft_strncmp(entry->d_name, "..", 3) != 0
				&& ft_strnstr(entry->d_name, d.env_var,
						ft_strlen(d.env_var)) != NULL)
				d.env_name = ft_strjoin(d.env_name, entry->d_name);
		}
		entry = readdir(dir);
	}
	return (d.env_name);
}

char	*wildcard(t_cmd *cur, t_data d)
{
	while (cur->cmd[d.i] != '\0')
	{
		d.i2 = d.i;
		while (cur->cmd[d.i] != '\0' && cur->cmd[d.i] != '*'
			&& cur->cmd[d.i + 1] != '.')
			d.i++;
		if (cur->cmd[d.i] == '\0')
			return (cur->cmd);
		d.temp = ft_strjoin12f(d.temp, ft_substr(cur->cmd, d.i2, d.i - d.i2));
		d.i++;
		d.i2 = d.i;
		while (cur->cmd[d.i] != '\0' && cur->cmd[d.i] != ' ')
			d.i++;
		d.env_var = ft_substr(cur->cmd, d.i2, d.i - d.i2);
		d.temp = ft_strjoin12f(d.temp, get_file(d));
	}
	free(cur->cmd);
	cur->cmd = d.temp;
	return (cur->cmd);
}
