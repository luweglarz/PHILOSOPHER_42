/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:31:19 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/13 14:58:13 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*checker_routine(void *philos)
{
	t_philo			**philosos;
	unsigned int	i;
	unsigned int	n;

	i = 0;
	philosos = (t_philo **)philos;
	n = philosos[i]->args->philo_amount;
	while (1)
	{
		i = 0;
		while (i < n - 1)
		{
			if (philosos[i]->is_dead == true)
				exit (1);
			i++;
		}
	}
	return (NULL);
}

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
			printf("%llu philo philo %d has died\n", get_time(philo), new_philo->num);
			new_philo->is_dead = true;
			sleep(1);
		}
	}
	 return (NULL);
}
