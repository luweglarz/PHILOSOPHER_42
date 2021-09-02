/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:00:03 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/02 15:32:09 by lweglarz         ###   ########.fr       */
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

# define THREAD_FAIL 1
# define MUTEX_FAIL 2

typedef uint64_t	t_millisecond;

typedef struct s_args
{
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
	bool			thinking;
	bool			eating;
	bool			sleeping;
	t_args			*args;
}				t_philo;

int		ft_atoi(const char *nptr);
void	error(int code, t_philo *philos);

#endif