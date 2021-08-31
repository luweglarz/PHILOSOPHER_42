/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:00:03 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/31 15:25:58 by lweglarz         ###   ########.fr       */
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
typedef uint64_t  millisecond;

typedef struct 	s_args
{
	unsigned int	philo_amount;
	unsigned int	times_philosopher_eat;
	millisecond		time_to_die;
	millisecond		time_to_eat;
	millisecond		time_to_sleep;
}				t_args;

typedef struct  s_philo
{
	pthread_t		id;
    bool    		thinking;
    bool    		eating;
    bool    		sleeping;
    pthread_mutex_t	forks;
}               t_philo;


int		ft_atoi(const char *nptr);
void	error(int code, t_philo *philos);

#endif