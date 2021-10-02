/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/10/02 21:56:04 by lweglarz         ###   ########.fr       */
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
	philo_write(philo, PHILO_SLEEP);
	my_usleep(philo->args->time_to_sleep, philo);
	philo_write(philo, PHILO_THINK);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->die_mutex);
	pthread_mutex_unlock(&philo->args->die_mutex);
	pthread_mutex_lock(&philo->args->fork_mutex[philo->right_fork]);
	philo_write(philo, PHILO_FORK);
	pthread_mutex_lock(&philo->args->fork_mutex[*philo->left_fork]);
	philo_write(philo, PHILO_FORK);
	philo_write(philo, PHILO_EAT);
	philo->last_eat = get_time(philo);
	my_usleep(philo->args->time_to_eat, philo);
	philo->meals--;
	pthread_mutex_unlock(&philo->args->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->args->fork_mutex[*philo->left_fork]);
	philo_sleep(philo);
}
