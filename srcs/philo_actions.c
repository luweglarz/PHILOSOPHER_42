/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/03 19:12:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	philo_eat(t_philo *philo)
{
	if (philo->args->forks > 1)
	{
		pthread_mutex_lock(&philo->args->mutex);
		philo->args->forks -= 2;
		printf("amount of forks %d\n", philo->args->forks);
		pthread_mutex_unlock(&philo->args->mutex);
		philo->has_eaten = true;
		printf("Philo %d has taken a fork \n", (int)philo->id);
		printf("Philo %d is eating \n", (int)philo->id);
	}
}