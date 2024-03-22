/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:19:30 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/11 11:53:23 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	conf_philo(t_table *table, char **argv, int argc)
{
	t_philo		*philo;
	t_philo		*temp;
	int			i;

	i = 0;
	while (i != table->nphilo)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (philo == NULL)
			return (printf("Marshal: Malloc error\n"));
		philo->id = i + 1;
		philo->neat = 0;
		philo->state = 0;
		philo->data = table;
		if (conf_philo2(philo, argv, argc) != 0)
			return (printf("Marshal: Input error\n"));
		ft_lstadd_back(&table->tphilo, philo);
		i++;
	}
	temp = table->tphilo;
	while (temp->nextphilo != NULL)
		temp = temp->nextphilo;
	temp->nextphilo = table->tphilo;
	table->lphilo = philo;
	return (0);
}

int	conf_philo2(t_philo *philo, char **argv, int argc)
{
	philo->tdead = ft_atoi(argv[2]);
	philo->teat = ft_atoi(argv[3]) * 1000;
	philo->tsleep = ft_atoi(argv[4]) * 1000;
	philo->ttdie = philo->tdead;
	philo->nextphilo = NULL;
	philo->nteat = -1;
	philo->neat = 0;
	philo->nphilo = ft_atoi(argv[1]);
	if (argc == 6)
	{
		philo->nteat = ft_atoi(argv[5]);
		if (philo->nteat <= 0)
			return (1);
	}
	if (philo->tdead < 1 || philo->teat < 1 || philo->tsleep < 1)
		return (1);
	conf_philo3(philo);
	return (0);
}

void	conf_philo3(t_philo *philo)
{
	if (philo->id == 1)
	{
		philo->fl = 0;
		philo->fr = philo->nphilo - 1;
	}
	else
	{
		philo->fl = philo->id - 1;
		philo->fr = philo->id - 2;
	}
}
