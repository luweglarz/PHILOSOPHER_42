/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:18:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/13 14:38:19 by lweglarz         ###   ########.fr       */
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
		i++;
	}
	return (philos);
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
	args.mutex = malloc(sizeof(pthread_mutex_t) * args.philo_amount);
	i = 0;
	while (i < args.philo_amount)
	{
		if (pthread_mutex_init(&args.mutex[i], NULL) != 0)
			error(MUTEX_FAIL, NULL);
		i++;
	}
	return (args);
}

void	*checker_thread(void *philos)
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

void	create_threads(t_args args, t_philo *philos)
{
	int				i;
	int				err;
	pthread_t		checker;

	i = 0;
	err = 0;
	while ((unsigned int)i < args.philo_amount)
	{
		err = pthread_create(&philos[i].id, NULL, philo_routine, &philos[i]);
		if (err != 0)
			error(THREAD_FAIL, philos);
		i++;
	}
	pthread_create(&checker, NULL, checker_thread, &philos);
	i = 0;
	while ((unsigned int)i < args.philo_amount + 1)
	{
		pthread_join(philos[i].id, NULL);
		i++;
	}
}
