/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:57:26 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/11 12:01:01 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routin(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo *)philo_v;
	if (philo->id % 2 == 0)
	{
		msg(philo, "is thinking");
		usleep(philo->teat);
	}
	if (philo->id == philo->data->lphilo->id
		&& philo->data->lphilo->id % 2 == 1)
	{
		msg(philo, "is thinking");
		usleep(philo->teat * 2);
	}
	routin2(philo);
	return (NULL);
}

int	routin2(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->fl]);
		pthread_mutex_lock(&philo->data->forks[philo->fr]);
		pthread_mutex_lock(&philo->data->dead);
		philo->ttdie = (ft_time() - philo->data->tstart) + philo->tdead;
		pthread_mutex_unlock(&philo->data->dead);
		if (print_eat(philo) == 1)
			return (1);
		usleep(philo->teat);
		pthread_mutex_unlock(&philo->data->forks[philo->fl]);
		pthread_mutex_unlock(&philo->data->forks[philo->fr]);
		pthread_mutex_lock(&philo->data->neatm);
		philo->neat++;
		pthread_mutex_unlock(&philo->data->neatm);
		if (msg(philo, "is sleeping") == 1)
			return (1);
		usleep(philo->tsleep);
		if (msg(philo, "is thinking") == 1)
			return (1);
		if (philo->nphilo % 2 == 1)
			usleep(philo->teat);
	}
}

void	simulasion(t_table *table)
{
	t_philo	*philo;
	int		i;

	start_simulation(table);
	philo = table->tphilo;
	i = 0;
	while (++i != table->nphilo)
	{
		pthread_mutex_lock(&philo->data->neatm);
		if (philo->neat != philo->nteat)
			i = 0;
		pthread_mutex_unlock(&philo->data->neatm);
		philo = philo->nextphilo;
		if (controll_sim(table) == 1)
			break ;
		usleep(50);
	}
	pthread_mutex_lock(&philo->data->endsimm);
	table->endsim = 0;
	pthread_mutex_unlock(&philo->data->endsimm);
	pthread_mutex_lock(&philo->data->print);
	if (i == table->nphilo)
		printf("All philosofer are full\n");
	pthread_mutex_unlock(&philo->data->print);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc != 6 && argc != 5)
		return (printf("Marshal: Input error\n"));
	if (conf_table(&table, argv) != 0)
		return (1);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]));
		printf("%d 1 died\n", ft_atoi(argv[2]));
		free_pars(&table);
		return (0);
	}
	if (conf_philo(&table, argv, argc) != 0)
		return (1);
	simulasion(&table);
	free_all(&table);
	return (0);
}
