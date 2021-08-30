/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:00:03 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/30 20:38:01 by user42           ###   ########.fr       */
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

# include "lib.h"

typedef unsigned long long  millisecond;

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
    bool    thinking;
    bool    eating;
    bool    sleeping;
    int     forks;
}               t_philo;

#endif