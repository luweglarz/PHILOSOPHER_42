/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:18:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/03 19:31:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_philo	set_philo(int i)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	philo.nb = i;
	return (philo);
}

t_philo	*create_philos(t_args *args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->philo_amount);
	while ((unsigned int)i < args->philo_amount)
	{
		philos[i] = set_philo(i);
		philos[i].args = args;
		i++;
	}
	return (philos);
}

t_args	set_args(char **av)
{
	t_args			args;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	args.origin_time = tv;
	args.philo_amount = (unsigned int)ft_atoi(av[1]);
	args.forks = args.philo_amount;
	args.time_to_die = (unsigned long long)ft_atoi(av[2]);
	args.time_to_eat = (unsigned long long)ft_atoi(av[3]);
	args.time_to_sleep = (unsigned long long)ft_atoi(av[4]);
	args.times_philosopher_eat = (unsigned int)ft_atoi(av[5]);
	if (pthread_mutex_init(&args.mutex, NULL) != 0)
		error(MUTEX_FAIL, NULL);
	return (args);
}

void	create_threads(t_args args, t_philo *philos)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while ((unsigned int)i < args.philo_amount)
	{
		err = pthread_create(&philos[i].id, NULL, philo_routine, &philos[i]);
		if (err != 0)
			error(THREAD_FAIL, philos);
		i++;
	}
	i = 0;
	while ((unsigned int)i < args.philo_amount)
	{
		pthread_join(philos[i].id, NULL);
		i++;
	}	
}
