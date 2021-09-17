/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 14:33:53 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/17 20:36:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_millisecond	to_mili(struct timeval tv)
{
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

t_millisecond	get_time(t_philo *philo)
{
	t_millisecond	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = to_mili(tv) - philo->args->origin_time;
	return (time);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;
	int	isnegative;

	nbr = 0;
	isnegative = 1;
	i = 0;
	while ((nptr[i] >= 8 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			isnegative = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (isnegative * nbr);
}

void	philo_write(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->args->write_mutex);
	if (status == PHILO_FORK)
		printf("%llu philo %d has taken a fork\n", get_time(philo), philo->num);
	else if (status == PHILO_EAT)
		printf("%llu philo %d is eating\n", get_time(philo), philo->num);
	else if (status == PHILO_DEATH)
	{
		printf("%llu philo %d died\n", get_time(philo), philo->num);
		philo->is_dead = true;
		sleep(10);
	}
	else if (status == PHILO_SLEEP)
		printf("%llu philo %d is sleeping \n", get_time(philo), philo->num);
	else if (status == PHILO_THINK)
		printf("%llu philo %d is thinking \n", get_time(philo), philo->num);
	pthread_mutex_unlock(&philo->args->write_mutex);
}
