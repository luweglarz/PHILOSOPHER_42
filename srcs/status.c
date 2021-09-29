/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/29 14:44:51 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_millisecond	get_actual_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit(0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(t_millisecond time)
{
	t_millisecond	start;

	start = get_actual_time();
	while ((get_actual_time() < time + start))
		usleep(1);
}

int	philo_death(t_millisecond timestamp, t_philo *philo)
{
	if (timestamp > philo->last_eat + philo->args->time_to_die)
		return (1);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	philo_write(philo, PHILO_SLEEP);
	my_usleep(philo->args->time_to_sleep);
	philo_write(philo, PHILO_THINK);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->fork_mutex[philo->right_fork]);
	philo_write(philo, PHILO_FORK);
	pthread_mutex_lock(&philo->args->fork_mutex[*philo->left_fork]);
	philo_write(philo, PHILO_FORK);
	philo_write(philo, PHILO_EAT);
	philo->last_eat = get_time(philo);
	my_usleep(philo->args->time_to_eat);
	philo->meals--;
	pthread_mutex_unlock(&philo->args->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->args->fork_mutex[*philo->left_fork]);
	philo_sleep(philo);
}
