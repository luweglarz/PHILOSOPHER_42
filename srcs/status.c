/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/13 15:05:36 by lweglarz         ###   ########.fr       */
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
	printf("%llu philo %d is sleeping \n", get_time(philo), philo->num);
	while (get_time(philo) < sleep_end)
	{
		if (philo_death(get_time(philo), philo) == 1)
		{
			printf("%llu philo %d has died\n", get_time(philo), philo->num);
			philo->is_dead = true;
			sleep(1);
		}
	}
	printf("%llu philo %d is thinking \n", get_time(philo), philo->num);
}

void	philo_eat(t_philo *philo)
{
	t_millisecond	eat_end;

	eat_end = 0;
	if (philo->num % 2 == 0 || philo->num == 0)
		usleep(0.5 * 1000);
	pthread_mutex_lock(&philo->args->mutex[*philo->forks[0]]);
	printf("%llu philo %d has taken a fork\n", get_time(philo), philo->num);
	pthread_mutex_lock(&philo->args->mutex[*philo->forks[1]]);
	printf("%llu philo %d has taken a fork\n", get_time(philo), philo->num);
	printf("%llu philo %d is eating\n", get_time(philo), philo->num);
	eat_end = get_time(philo) + philo->args->time_to_eat;
	while (get_time(philo) < eat_end)
	{
		if (philo_death(get_time(philo), philo) == 1)
		{
			printf("%llu philo %d has died\n", get_time(philo), philo->num);
			philo->is_dead = true;
			sleep(1);
		}
	}
	philo->last_eat = get_time(philo);
	pthread_mutex_unlock(&philo->args->mutex[*philo->forks[0]]);
	pthread_mutex_unlock(&philo->args->mutex[*philo->forks[1]]);
}
