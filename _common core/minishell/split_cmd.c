/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:27:25 by aanghi            #+#    #+#             */
/*   Updated: 2024/05/07 14:09:53 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_cmd(t_master *master, t_data d)
{
	t_cmd	*cmd;

	if (d.i2 - d.i == 0)
		return ;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		write(2, "Marshal: Malloc error\n", 22);
		exit(EXIT_FAILURE);
	}
	cmd->cmd = ft_substr(master->input, d.i2, d.i - d.i2);
	cmd->pipe = d.pipe;
	cmd->next = NULL;
	cmd->or = d.or;
	ft_lstadd_back(&master->lcmd, cmd);
	master->ncmd++;
}

static void	sup1(t_master *master, t_data *d)
{
	if (d->or_1 == 1)
	{
		d->or_1 = 0;
		d->or = 1;
	}
	if (d->pipe_1 == 1)
	{
		d->pipe_1 = 0;
		d->pipe = 2;
	}
	if (master->input[d->i] == '|' && master->input[d->i + 1] == '|')
		d->or_1 = 1;
	else if (master->input[d->i] == '|')
	{
		d->pipe_1 = 1;
		d->pipe = 1;
	}
	add_cmd(master, *d);
}

void	split_cmd(t_master *master)
{
	t_data		d;

	d.i = 0;
	d.or = 0;
	d.pipe = 0;
	d.pipe_1 = 0;
	d.or_1 = 0;
	master->npipe = count_pipe(master->input, '|');
	while (master->input[d.i] != '\0')
	{
		d.i2 = d.i;
		while (master->input[d.i] != '\0' && master->input[d.i] != '|'
			&& master->input[d.i] != '&')
		{
			spik_duote(&d.i, master->input, '\'');
			spik_duote(&d.i, master->input, '\"');
			d.i++;
		}
		sup1(master, &d);
		if ((master->input[d.i] == '&' && master->input[d.i + 1] == '&')
			|| (master->input[d.i] == '|' && master->input[d.i + 1] == '|'))
			d.i += 1;
		if (master->input[d.i] != '\0')
			d.i++;
	}
}
