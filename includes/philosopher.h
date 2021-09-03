/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:00:03 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/03 19:30:23 by user42           ###   ########.fr       */
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

typedef uint64_t	t_millisecond;

typedef struct s_args
{
	struct timeval	origin_time;
	unsigned int	philo_amount;
	unsigned int	forks;
	unsigned int	times_philosopher_eat;
	t_millisecond	time_to_die;
	t_millisecond	time_to_eat;
	t_millisecond	time_to_sleep;
	pthread_mutex_t	mutex;
}				t_args;

typedef struct s_philo
{
	pthread_t		id;
	int				nb;
	bool			has_thought;
	bool			has_eaten;
	bool			has_slept;
	t_args			*args;
}				t_philo;

void			create_threads(t_args args, t_philo *philos);

t_philo			set_philo(int i);
t_philo			*create_philos(t_args *args);
t_args			set_args(char **av);

void			*philo_routine(void *philo);
void			philo_eat(t_philo *philo);

t_millisecond	to_mili(struct timeval tv);
int				ft_atoi(const char *nptr);
void			error(int code, t_philo *philos);

#endif