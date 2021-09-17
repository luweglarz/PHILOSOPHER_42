/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:31:19 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/17 20:37:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*death_checkerr(void *philo)
{
	t_philo			*new_philo;

	new_philo = (t_philo *)philo;
	while (1)
	{
		if (philo_death(get_time(new_philo), new_philo) == 1)
			philo_write(new_philo, PHILO_DEATH);
	}

}

void	create_death_checker(t_philo *philo)
{
	int err;
	pthread_t		thread_checker;

	err = 0;
	err = pthread_create(&thread_checker, NULL, death_checkerr, philo);
	if (err != 0)
		error(THREAD_FAIL, philo);
}

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;

	new_philo = (t_philo *)philo;
	create_death_checker(new_philo);
	while (1)
	{
		philo_eat(new_philo);
		philo_sleep(new_philo);
		if (new_philo->meals == 0)
		{
			while (1)
			{}
		}
	}
	 return (NULL);
}
