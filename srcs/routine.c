/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:31:19 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/14 19:36:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;

	new_philo = (t_philo *)philo;
	while (1)
	{
		philo_eat(new_philo);
		philo_sleep(new_philo);
		if (philo_death(get_time(philo), new_philo) == 1)
		{
			philo_write(philo, PHILO_DEATH);
			new_philo->is_dead = true;
			sleep(1);
		}
	}
	 return (NULL);
}
