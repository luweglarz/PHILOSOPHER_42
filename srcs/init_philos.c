/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:15:02 by user42            #+#    #+#             */
/*   Updated: 2021/10/01 23:13:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static t_philo	set_philo(int i)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	philo.num = i;
	return (philo);
}

static void	pointer_on_right_fork(t_philo *philos)
{
	unsigned int	i;
	unsigned int	philo_amount;

	i = 0;
	philo_amount = philos->args->philo_amount;
	while (i < philo_amount)
	{
		philos[i].left_fork = &philos[i + 1].right_fork;
		i++;
	}
}

t_philo	*create_philos(t_args *args, int ac)
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
		philos[i].right_fork = i;
		if (philos[i].num == args->philo_amount - 1)
			j = 0;
		if (ac == 6)
			philos[i].meals = args->times_philosopher_eat;
		else
			philos[i].meals = -1000;
		i++;
	}
	pointer_on_right_fork(philos);
	return (philos);
}
