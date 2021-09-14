/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:18:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 23:47:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_philo	set_philo(int i)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	philo.num = i;
	return (philo);
}

t_philo	*create_philos(t_args *args)
{
	int		i;
	int		j;
	t_philo	*philos;

	i = 0;
	j = 0;
	philos = malloc(sizeof(t_philo) * args->philo_amount);
	while ((unsigned int)i < args->philo_amount)
	{
		philos[i] = set_philo(i);
		philos[i].args = args;
		philos[i].forks[0] = &args->forks[j++];
		philos[i].forks[1] = &args->forks[j];
		philos[i].meals = args->times_philosopher_eat;
		i++;
	}
	return (philos);
}

void	init_mutexes(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->philo_amount)
	{
		if (pthread_mutex_init(&args->fork_mutex[i], NULL) != 0)
			error(MUTEX_FAIL, NULL);
		i++;
	}
	if (pthread_mutex_init(&args->write_mutex, NULL) != 0)
		error(MUTEX_FAIL, NULL);
}

t_args	set_args(char **av)
{
	unsigned int	i;
	t_args			args;

	i = 0;
	args.philo_amount = (unsigned int)ft_atoi(av[1]);
	args.forks = malloc(sizeof(int) * args.philo_amount);
	while (i < args.philo_amount)
	{
		args.forks[i] = i;
		i++;
	}
	args.time_to_die = (unsigned long long)ft_atoi(av[2]);
	args.time_to_eat = (unsigned long long)ft_atoi(av[3]);
	args.time_to_sleep = (unsigned long long)ft_atoi(av[4]);
	args.times_philosopher_eat = (unsigned int)ft_atoi(av[5]);
	args.fork_mutex = malloc(sizeof(pthread_mutex_t) * args.philo_amount);
	init_mutexes(&args);
	return (args);
}

void	create_threads(t_args args, t_philo *philos)
{
	int				i;
	int				err;

	i = 0;
	err = 0;
	while ((unsigned int)i < args.philo_amount)
	{
		err = pthread_create(&philos[i].id, NULL, philo_routine, &philos[i]);
		if (err != 0)
			error(THREAD_FAIL, philos);
		i++;
	}
}
