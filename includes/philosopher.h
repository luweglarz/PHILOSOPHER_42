/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:00:03 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/13 14:33:14 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>
# include <stdint.h>

# define ARGS_FAIL 1
# define THREAD_FAIL 2
# define MUTEX_FAIL 3

typedef unsigned long long	t_millisecond;

typedef struct s_args
{
	t_millisecond	origin_time;
	unsigned int	philo_amount;
	int				*forks;
	unsigned int	times_philosopher_eat;
	t_millisecond	time_to_die;
	t_millisecond	time_to_eat;
	t_millisecond	time_to_sleep;
	pthread_mutex_t	*mutex;	
}				t_args;

typedef struct s_philo
{
	pthread_t		id;
	unsigned int	num;
	int				*forks[2];
	bool			is_dead;
	t_millisecond	last_eat;
	t_args			*args;
}				t_philo;

void			create_threads(t_args args, t_philo *philos);

t_philo			set_philo(int i);
t_philo			*create_philos(t_args *args);
t_args			set_args(char **av);

void			*philo_routine(void *philo);

void			philo_sleep(t_philo *philo);
void			philo_eat(t_philo *philo);
int				philo_death(t_millisecond timestamp, t_philo *philo);

t_millisecond	to_mili(struct timeval tv);
t_millisecond	get_time(t_philo *philo);
int				ft_atoi(const char *nptr);
void			error(int code, t_philo *philos);

#endif