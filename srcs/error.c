/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:57:17 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/03 19:24:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	free_philos(t_philo **philos)
{
	int	i;

	i = 0;
	if (philos)
	{
		while (philos[i])
		{
			free(philos[i]);
			i++;
		}
		free(philos);
		philos = NULL;
	}
}

void	error(int code, t_philo *philos)
{
	if (code == ARGS_FAIL)
	{
		write(2, "Philo should takes 5 arguments:\n", 33);
		write(2, "1: number_of_philosophers\n2:", 29);
		write(2, "2: time_to_die\n", 16);
		write(2, "3: time_to_eat\n", 16);
		write(2, "4: time_to_sleep\n", 18);
		write(2, "5: number_of_times_each_philosopher_must_eat", 45);
	}
	if (code == THREAD_FAIL)
		write(2, "The thread couldn't be created\n", 32);
	if (code == MUTEX_FAIL)
		write(2, "The mutex couldn't be created\n", 31);
	free_philos(&philos);
	exit(code);
}
