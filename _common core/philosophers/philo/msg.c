/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:54:19 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/11 10:40:19 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->endsimm);
	if (philo->data->endsim == 0)
	{
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->endsimm);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->endsimm);
	printf("%ld %d %s\n", (ft_time() - philo->data->tstart), philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

int	msg_dead(t_philo *philo)
{
	msg(philo, "died");
	pthread_mutex_lock(&philo->data->endsimm);
	philo->data->endsim = 0;
	pthread_mutex_unlock(&philo->data->endsimm);
	pthread_mutex_unlock(&philo->data->dead);
	return (1);
}

int	print_eat(t_philo *philo)
{
	if (msg(philo, "has taken a fork") == 1)
		return (1);
	if (msg(philo, "has taken a fork") == 1)
		return (1);
	if (msg(philo, "is eating") == 1)
		return (1);
	return (0);
}
