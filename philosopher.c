/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/02 15:32:37 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

t_philo	set_philo(t_args *args, int i)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	return (philo);
}

t_philo	*create_philos(t_args *args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->philo_amount);
	while (i < args->philo_amount)
	{
		philos[i] = set_philo(args, i);
		philos[i].args = args;
		i++;
	}
	return (philos);
}

t_args	set_args(char **av)
{
	t_args	args;

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

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;
	t_millisecond	time;
	struct timeval	tv1;
	struct timeval	tv2;

	new_philo = (t_philo *)philo;
	time = 0;
	gettimeofday(&tv2, NULL);
	while (1)
	{
		pthread_mutex_lock(&new_philo->args->mutex);
		if (new_philo->args->forks > 1)
		{
			new_philo->args->forks -= 2;
			printf("amount of forks %d\n", new_philo->args->forks);
			printf("Philo id %d has taken a fork \n", (int)new_philo->id);
			while (time != new_philo->args->time_to_eat)
			{
				gettimeofday(&tv1, NULL);
				if (time != (tv1.tv_sec) * 1000 + (tv1.tv_usec) / 1000 - (tv2.tv_sec) * 1000 + (tv2.tv_usec) / 1000)
				{
					time = (tv1.tv_sec) * 1000 + ((tv1.tv_usec) / 1000 - (tv2.tv_sec) * 1000 + (tv2.tv_usec) / 1000);
					//printf("le time %llu\n", time);
				}
			}
			printf("time:%llu Philo id %d has eaten\n",time, (int)new_philo->id);;
		 }
		pthread_mutex_unlock(&new_philo->args->mutex);
 	}
	 return (NULL);
}

int	main(int ac, char **av)
{
	int		i;
	int		err;
	t_args	args;
	t_philo	*philos;

	i = 0;
	if (ac == 6)
	{
		args = set_args(av);
		philos = create_philos(&args);
		while (i < args.philo_amount)
		{
			err = pthread_create(&philos[i].id, NULL, philo_routine, &philos[i]);
			if (err != 0)
				error(THREAD_FAIL, philos);
			i++;
		}
		i = 0;
		while (i < args.philo_amount)
		{
			pthread_join(philos[i].id, NULL);
			i++;
		}
	}
	else
	{
		write(2, "Philo should takes 5 arguments:\n", 33);
		write(2, "1: number_of_philosophers\n2:", 29);
		write(2, "2: time_to_die\n", 16);
		write(2, "3: time_to_eat\n", 16);
		write(2 ,"4: time_to_sleep\n", 18);
		write(2, "5: number_of_times_each_philosopher_must_eat", 45);
	}
}
