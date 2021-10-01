/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/10/01 23:13:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

bool	check_end(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->args->times_philosopher_eat != -1000)
	{
		while (philos[i].meals <= 0 && i < philos->args->philo_amount - 1)
			i++;
		if (i == philos->args->philo_amount - 1)
			return (true);
	}
	return (false);
}

void	destroy_mutexes(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_amount)
	{
		pthread_mutex_destroy(&args->fork_mutex[i]);
		i++;
	}
	free(args->fork_mutex);
	pthread_mutex_destroy(&args->write_mutex);
}

void	*deathnmeal_checker(t_philo *philos)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = philos[i].args->philo_amount;
	while (1)
	{
		i = 0;
		while (i < n)
		{
			if (philos[i].is_dead == true || check_end(philos) == true)
			{
				philos->args->end = true;
				usleep(2000000);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args			args;
	t_philo			*philos;
	struct timeval	tv;

	if (ac == 6 || ac == 5)
	{
		args = set_args(av, ac);
		philos = create_philos(&args, ac);
		gettimeofday(&tv, NULL);
		args.origin_time = to_mili(tv);
		create_threads(args, philos);
		deathnmeal_checker(philos);
		destroy_mutexes(&args);
		free(philos);
	}
	else
		error(ARGS_FAIL, NULL);
}
