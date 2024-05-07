/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 08:46:41 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/11 22:38:18 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	expand(t_cmd *cmd, t_data *d, int i)
{
	int		i2;

	d->temp = malloc(ft_strlen(cmd->cmd) + ft_strlen(d->env_var) + 1);
	if (d->temp == NULL)
		exit(write(2, "Marshal: Malloc error\n", 23));
	while (cmd->cmd[++i] != '$')
		d->temp[i] = cmd->cmd[i];
	i2 = 0;
	while (d->env_var[i2] != '\0')
	{
		d->temp[i + i2] = d->env_var[i2];
		i2++;
	}
	while (cmd->cmd[i + ft_strlen(d->env_name) + 1] != '\0')
	{
		d->temp[i + i2] = cmd->cmd[i + ft_strlen(d->env_name) + 1];
		i++;
	}
	d->temp[i + i2] = '\0';
	free(cmd->cmd);
	free(d->env_name);
	free(d->env_var);
	d->env_var = NULL;
	cmd->cmd = d->temp;
}

static void	set_expand(t_master *master, t_cmd *cmd, t_data *d)
{
	while (cmd->cmd[d->i] != '\0' && cmd->cmd[d->i] != ' '
		&& cmd->cmd[d->i] != '\'' && cmd->cmd[d->i] != '\"'
		&& cmd->cmd[d->i] != '$')
		d->i++;
	if (cmd->cmd[d->i] == '\'' || cmd->cmd[d->i] == '\"'
		|| cmd->cmd[d->i] == ' ' || cmd->cmd[d->i] == '$')
		d->i--;
	d->env_name = ft_substr(cmd->cmd, d->i2, d->i - d->i2 + 1);
	d->env_var = get_env(master, d->env_name);
	if (d->env_var == NULL)
		d->env_var = ft_strjoin("\0", "\0");
	expand(cmd, d, -1);
}

char	*expander(t_master *master, t_cmd *cmd, t_data d)
{
	while (cmd->cmd[d.i] != '\0')
	{
		if (cmd->cmd[d.i] == '\'' && d.dquote == 0)
			d.quote = 1;
		if (cmd->cmd[d.i] == '\"' && d.quote == 0)
			d.dquote = 1;
		if (cmd->cmd[d.i] == '$' && d.quote == 0)
		{
			d.i++;
			d.i2 = d.i;
			if (cmd->cmd[d.i] == '?')
			{
				d.env_name = ft_substr(cmd->cmd, d.i2, d.i - d.i2 + 1);
				d.env_var = ft_itoa(g_code_exit);
				if (d.env_var != NULL)
					expand(cmd, &d, -1);
			}
			else
				set_expand(master, cmd, &d);
			d.i = 0;
		}
		if (cmd->cmd[d.i] != '\0')
			d.i++;
	}
	return (cmd->cmd);
}
