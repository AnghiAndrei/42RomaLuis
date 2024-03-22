/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiliti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:02:09 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/11 12:01:26 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	controll_sim(t_table *tb)
{
	pthread_mutex_lock(&tb->dead);
	if (tb->tphilo->ttdie < (ft_time() - tb->tstart))
		return (msg_dead(tb->tphilo));
	else if (tb->tphilo->nextphilo->ttdie < (ft_time() - tb->tstart))
		return (msg_dead(tb->tphilo->nextphilo));
	else if (tb->nphilo % 2 == 1
		&& tb->lphilo->ttdie < (ft_time() - tb->tstart))
		return (msg_dead(tb->lphilo));
	pthread_mutex_unlock(&tb->dead);
	return (0);
}

uint64_t	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	start_simulation(t_table *table)
{
	t_philo	*philo;
	int		i;

	philo = table->tphilo;
	i = 0;
	table->tstart = ft_time();
	while (table->nphilo != i)
	{
		pthread_create(&philo->thread, NULL, routin, philo);
		philo = philo->nextphilo;
		i++;
	}
}

void	free_all(t_table *table)
{
	t_philo		*cur;
	t_philo		*next;
	int			i;

	i = 0;
	cur = table->tphilo;
	while (i++ != table->nphilo)
	{
		pthread_join(cur->thread, NULL);
		next = cur->nextphilo;
		free(cur);
		cur = next;
	}
	i = 0;
	while (i != table->nphilo)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->endsimm);
	pthread_mutex_destroy(&table->dead);
	pthread_mutex_destroy(&table->neatm);
	free(table->forks);
}

void	free_pars(t_table *table)
{
	int			i;

	i = 0;
	while (i != table->nphilo)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->endsimm);
	pthread_mutex_destroy(&table->dead);
	pthread_mutex_destroy(&table->neatm);
	free(table->forks);
}
