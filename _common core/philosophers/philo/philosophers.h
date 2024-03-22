/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:01:16 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/11 12:01:41 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				fl;
	int				fr;
	int				teat;
	int				neat;
	int				state;
	int				tdead;
	int				nteat;
	int				tsleep;
	int				nphilo;
	uint64_t		ttdie;
	pthread_t		thread;
	struct s_table	*data;
	struct s_philo	*nextphilo;
}				t_philo;

typedef struct s_table
{
	t_philo			*tphilo;
	t_philo			*lphilo;
	uint64_t		tstart;
	int				nphilo;
	int				endsim;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	pthread_mutex_t	neatm;
	pthread_mutex_t	endsimm;
}				t_table;

int			conf_philo2(t_philo *philo, char **argv, int argc);
int			conf_philo(t_table *table, char **argv, int argc);
int			routin_utilitis2(t_philo *philo, int c1, int c2);
void		ft_lstadd_back(t_philo **lst, t_philo *new);
int			conf_table(t_table *table, char **argv);
void		start_simulation(t_table *table);
int			msg(t_philo *philo, char *str);
int			controll_sim(t_table *table);
int			ft_atoi(const char *string);
void		conf_philo3(t_philo *philo);
int			conf_mutex(t_table *table);
int			conf_fork(t_table *table);
int			print_eat(t_philo *philo);
void		free_pars(t_table *table);
void		free_all(t_table *table);
int			msg_dead(t_philo *philo);
int			routin2(t_philo *philo);
void		*routin(void *philo_v);
uint64_t	ft_time(void);
