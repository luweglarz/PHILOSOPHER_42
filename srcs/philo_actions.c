/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/07 16:59:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_millisecond	get_time(t_philo *philo)
{
	t_millisecond	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = to_mili(tv) - philo->args->origin_time;
	return (time);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex);
	if (philo->forks[0]->available == true && philo->has_eaten == false)
	{
		printf("%lu philo %d has taken a fork num %d\n", get_time(philo), philo->num, philo->forks[0]->num);
		philo->forks[0]->available = false;
		philo->forks[0]->owner = philo;
	}
	if (philo->forks[1]->available == true && philo->has_eaten == false)
	{
		printf("%lu philo %d has taken a fork num %d\n", get_time(philo), philo->num, philo->forks[1]->num);
		philo->forks[1]->available = false;
		philo->forks[1]->owner = philo;
	}
	// pthread_mutex_unlock(&philo->args->mutex);
	if (get_time(philo) == philo->args->time_to_eat && philo->forks[0]->owner == philo && philo == philo->forks[1]->owner)
		printf("%lu philo %d has eaten\n", get_time(philo), philo->num);
	pthread_mutex_unlock(&philo->args->mutex);
}

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;
	// t_millisecond	time;
	// struct timeval	tv;

	new_philo = (t_philo *)philo;
	// time = 0;
	while (1)
	{
		// gettimeofday(&tv, NULL);
		// time = to_mili(tv);
		philo_eat(new_philo);	
	}
	 return (NULL);
}
