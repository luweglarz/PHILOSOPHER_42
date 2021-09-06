/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/06 22:33:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex);
	// if (philo->forks[0]->available == true)
	// {
	// 	printf("Philo %u has taken the fork nb %d\n", philo->num, philo->forks[1]->num);
	//  	philo->forks[0]->available = false;
	// }
	pthread_mutex_unlock(&philo->args->mutex);
	philo->has_eaten = true;
	// printf("Philo %d has taken a fork \n", (int)philo->id);
	// printf("Philo %d is eating \n", (int)philo->id);
}

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;
	t_millisecond	time;
	struct timeval	tv;

	new_philo = (t_philo *)philo;
	time = 0;
	while (1)
	{
		gettimeofday(&tv, NULL);
		time = to_mili(tv);
		philo_eat(new_philo);
	}
	 return (NULL);
}
