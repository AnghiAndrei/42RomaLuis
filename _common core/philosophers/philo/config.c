/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:09:16 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/11 11:53:26 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	conf_table(t_table *table, char **argv)
{
	table->nphilo = ft_atoi(argv[1]);
	table->tphilo = NULL;
	table->endsim = 1;
	table->tstart = 0;
	if (table->nphilo <= 0)
		return (printf("Marshal: Input error\n"));
	if (conf_mutex(table) == 1)
		return (printf("Marshal: Mutex error\n"));
	if (conf_fork(table) == 1)
		return (printf("Marshal: Malloc/Mutex error\n"));
	return (0);
}

int	conf_fork(t_table *table)
{
	int	i;

	table->forks = NULL;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nphilo);
	if (table->forks == NULL)
		return (1);
	i = 0;
	while (i != table->nphilo)
	{
		if (pthread_mutex_init(&table->forks[i++], NULL))
			return (2);
	}
	return (0);
}

int	conf_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->print, NULL))
		return (1);
	if (pthread_mutex_init(&table->endsimm, NULL))
		return (1);
	if (pthread_mutex_init(&table->dead, NULL))
		return (1);
	if (pthread_mutex_init(&table->neatm, NULL))
		return (1);
	return (0);
}
