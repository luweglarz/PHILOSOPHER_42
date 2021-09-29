/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:31:19 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/29 14:55:33 by lweglarz         ###   ########.fr       */
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
		if (new_philo->args->end == true || new_philo->is_dead == true)
			break ;
	}
	return (NULL);
}

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;

	new_philo = (t_philo *)philo;
	if (new_philo->num % 2 == 0)
		usleep(5000);
	while (1)
	{
		if (new_philo->args->end == true || new_philo->is_dead == true)
			break ;
		philo_eat(new_philo);
		if (new_philo->args->end == true || new_philo->is_dead == true)
			break ;
	}
	return (NULL);
}
