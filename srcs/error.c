/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:57:17 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/31 15:37:41 by lweglarz         ###   ########.fr       */
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
	if (code == THREAD_FAIL)
		write(2, "The thread couldn't be created\n", 32);
	free_philos(&philos);
	exit(code);
}
