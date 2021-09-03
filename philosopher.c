/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/03 19:18:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;
	t_millisecond	time;
	struct timeval	tv;

	new_philo = (t_philo *)philo;
	time = 0;
	while (1)
	{
		gettimeofday(&tv, NULL);
		time = to_mili(tv);
		philo_eat(new_philo);
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
		error(ARGS_FAIL, NULL);
}
