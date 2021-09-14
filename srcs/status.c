/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 23:58:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	philo_write(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->args->write_mutex);
	if (status == PHILO_FORK)
		printf("%llu philo %d has taken a fork\n", get_time(philo), philo->num);
	else if (status == PHILO_EAT)
		printf("%llu philo %d is eating\n", get_time(philo), philo->num);
	else if (status == PHILO_DEATH)
		printf("%llu philo %d died\n", get_time(philo), philo->num);
	else if (status == PHILO_SLEEP)
		printf("%llu philo %d is sleeping \n", get_time(philo), philo->num);
	else if (status == PHILO_THINK)
		printf("%llu philo %d is thinking \n", get_time(philo), philo->num);
	pthread_mutex_unlock(&philo->args->write_mutex);
}

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
		if (philo_death(get_time(philo), philo) == 1)
		{
			philo_write(philo, PHILO_DEATH);
			philo->is_dead = true;
			sleep(1);
		}
	}
	philo_write(philo, PHILO_THINK);
}

void	philo_eat(t_philo *philo)
{
	t_millisecond	eat_end;

	eat_end = 0;
	if (philo->num % 2 == 0 || philo->num == 0)
		usleep(500);
	pthread_mutex_lock(&philo->args->fork_mutex[*philo->forks[0]]);
	philo_write(philo, PHILO_FORK);
	pthread_mutex_lock(&philo->args->fork_mutex[*philo->forks[1]]);
	philo_write(philo, PHILO_FORK);
	philo_write(philo, PHILO_EAT);
	eat_end = get_time(philo) + philo->args->time_to_eat;
	while (get_time(philo) < eat_end)
	{
		if (philo_death(get_time(philo), philo) == 1)
		{
			philo_write(philo, PHILO_DEATH);
			philo->is_dead = true;
			sleep(1);
		}
	}
	philo->meals--;
	philo->last_eat = get_time(philo);
	pthread_mutex_unlock(&philo->args->fork_mutex[*philo->forks[0]]);
	pthread_mutex_unlock(&philo->args->fork_mutex[*philo->forks[1]]);
}
