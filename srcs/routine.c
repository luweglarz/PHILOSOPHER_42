/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:31:19 by lweglarz          #+#    #+#             */
/*   Updated: 2021/10/02 22:09:35 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*death_checker(void *philo)
{
	t_philo			*new_philo;

	new_philo = (t_philo *)philo;
	while (1)
	{
		if (philo_death(get_time(new_philo), new_philo) == 1)
			philo_write(new_philo, PHILO_DEATH);
		pthread_mutex_lock(&new_philo->args->die_mutex);
		if (new_philo->args->end == true || new_philo->is_dead == true)
			break ;
		pthread_mutex_unlock(&new_philo->args->die_mutex);
	}
	return (NULL);
}

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;

	new_philo = (t_philo *)philo;
	if (new_philo->num % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&new_philo->args->end_mutex);
		if (new_philo->args->end == true || new_philo->is_dead == true)
		{
			pthread_mutex_unlock(&new_philo->args->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&new_philo->args->end_mutex);
		philo_eat(new_philo);
		pthread_mutex_lock(&new_philo->args->end_mutex);
		if (new_philo->args->end == true || new_philo->is_dead == true)
		{
			pthread_mutex_unlock(&new_philo->args->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&new_philo->args->end_mutex);
	}
	return (NULL);
}
