/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/22 19:38:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

bool	check_end(t_philo *philos)
{
	int i;

	i = 0;
	while (philos[i].routine_id != 0 && philos[i].meals == 0)
		i++;
	if (philos->args->philo_amount % 2 == 0)
		i--;
	if (i == philos->args->philo_amount)
		return (true);
	return (false);
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
			if (philos[i].is_dead == true)
			{
				philos->args->end = true;
				sleep(1);
				return (NULL);
			}
			if (check_end(philos) == true)
			{
				philos->args->end = true;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
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

int	main(int ac, char **av)
{
	t_args			args;
	t_philo			*philos;
	struct timeval	tv;

	if (ac == 6)
	{
		args = set_args(av);
		philos = create_philos(&args);
		gettimeofday(&tv, NULL);
		args.origin_time = to_mili(tv);
		create_threads(args, philos);
		deathnmeal_checker(philos);
		destroy_mutexes(&args);
	}
	else
		error(ARGS_FAIL, NULL);
}
