/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:18:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/17 22:33:19 by user42           ###   ########.fr       */
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

void	pointer_on_right_fork(t_philo *philos)
{
	unsigned int	i;
	unsigned int	philo_amount;

	i = 0;
	philo_amount = philos->args->philo_amount;
	while (i < philo_amount)
	{
		if (philos[i].num == 0)
			philos[i].right_fork = &philos[philo_amount - 1].left_fork;
		else
			philos[i].right_fork = &philos[i - 1].left_fork;
		i++;
	}
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
		philos[i].left_fork = i;
		if (philos[i].num == args->philo_amount - 1)
			j = 0;
		philos[i].meals = args->times_philosopher_eat;
		i++;
	}
	pointer_on_right_fork(philos);
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
	args.time_to_die = (unsigned long long)ft_atoi(av[2]);
	args.time_to_eat = (unsigned long long)ft_atoi(av[3]);
	args.time_to_sleep = (unsigned long long)ft_atoi(av[4]);
	args.times_philosopher_eat = (unsigned int)ft_atoi(av[5]);
	args.fork_mutex = malloc(sizeof(pthread_mutex_t) * args.philo_amount);
	init_mutexes(&args);
	return (args);
}

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
	i = 0;
	while ((unsigned int)i < args.philo_amount)
	{
		err = pthread_create(&philos[i].id, NULL, death_checkerr, &philos[i]);
		if (err != 0)
			error(THREAD_FAIL, philos);
		i++;
	}
}
