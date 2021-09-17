/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/15 20:28:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

bool	check_end(t_philo *philos)
{
	int i;

	i = 0;
	while (philos[i].id != 0 && philos[i].meals == 0)
		i++;
	//i--;
	if (i == philos->args->philo_amount)
		return (true);
	return (false);
}

void	*death_checker(t_philo *philos)
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
				exit (1);
			if (check_end(philos) == true)
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
