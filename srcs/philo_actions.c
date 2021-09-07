/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/07 22:05:59 by user42           ###   ########.fr       */
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
	if (philo->num == 2 && (philo->forks[0]->available == 1 || philo->forks[1]->available))
	printf("le philo %d fork 0 %u fork 1 %u\n", philo->num, philo->forks[0]->available, philo->forks[1]->available);
	if (philo->forks[0]->available == true)
	{
		printf("%lu philo %d has taken a fork num %d\n", get_time(philo), philo->num, philo->forks[0]->num);
		philo->forks[0]->available = false;
		philo->forks[0]->owner = philo;
	}
	if (philo->forks[1]->available == true)
	{
		printf("%lu philo %d has taken a fork num %d\n", get_time(philo), philo->num, philo->forks[1]->num);
		philo->forks[1]->available = false;
		philo->forks[1]->owner = philo;
	}
	if (philo->forks[0]->owner == philo && philo == philo->forks[1]->owner &&
		philo->forks[0]->available == false && philo->forks[1]->available == false &&
		philo->has_eaten == false)
		{
		printf("%lu philo %d is eating\n", get_time(philo), philo->num);
		philo->has_eaten = true;
		}
	pthread_mutex_unlock(&philo->args->mutex);
	if (philo->has_eaten == true)
	{
		while (get_time(philo) != philo->args->time_to_eat)
		{
			//Philo 2 ne prend pas son autre fork car cette boucle tourne à l'infini
		}
		pthread_mutex_lock(&philo->args->mutex);
		philo->forks[0]->available = true;
		philo->forks[1]->available = true;
		pthread_mutex_unlock(&philo->args->mutex);
		sleep(100000);
	}
}

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;

	new_philo = (t_philo *)philo;
	while (1)
	{
		philo_eat(new_philo);

	}
	 return (NULL);
}
