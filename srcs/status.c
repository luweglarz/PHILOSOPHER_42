/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/17 22:35:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	philo_death(t_millisecond timestamp, t_philo *philo)
{
	if (timestamp > philo->last_eat + philo->args->time_to_die)
		return (1);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	t_millisecond	sleep_end;

	sleep_end = get_time(philo) + philo->args->time_to_sleep;
	philo_write(philo, PHILO_SLEEP);
	while (get_time(philo) < sleep_end)
	{
		usleep(100);
	}
	philo_write(philo, PHILO_THINK);
}

void	philo_eat(t_philo *philo)
{
	t_millisecond	eat_end;

	eat_end = 0;
	if (philo->num % 2 == 0)
		usleep(10000);
	pthread_mutex_lock(&philo->args->fork_mutex[philo->left_fork]);
	philo_write(philo, PHILO_FORK);
	pthread_mutex_lock(&philo->args->fork_mutex[*philo->right_fork]);
	philo_write(philo, PHILO_FORK);
	philo_write(philo, PHILO_EAT);
	eat_end = get_time(philo) + philo->args->time_to_eat;
	philo->last_eat = get_time(philo);
	while (get_time(philo) < eat_end)
	{
		usleep(100);
	}
	philo->meals--;
	pthread_mutex_unlock(&philo->args->fork_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->args->fork_mutex[*philo->right_fork]);
}
