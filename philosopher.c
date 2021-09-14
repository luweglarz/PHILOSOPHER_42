/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/14 23:18:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

void	*death_checker(t_philo *philos)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = philos[i].args->philo_amount;
	while (1)
	{
		i = 0;
		while (i < n - 1)
		{
			if (philos[i].is_dead == true)
				exit (1);
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

	if (ac == 6)
	{
		args = set_args(av);
		philos = create_philos(&args);
		gettimeofday(&tv, NULL);
		args.origin_time = to_mili(tv);
		create_threads(args, philos);
		death_checker(philos);
	}
	else
		error(ARGS_FAIL, NULL);
}
