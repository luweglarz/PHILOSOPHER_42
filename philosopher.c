/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/31 15:36:17 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

t_philo	set_philo(t_args args, int i)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	return (philo);
}

t_philo	*create_philos(t_args args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args.philo_amount);
   	while (i < args.philo_amount)
    {
		philos[i] = set_philo(args, i);
		if (pthread_mutex_init(&philos[i].forks, NULL) != 0)
			error(MUTEX_FAIL, philos);
		i++;
    }
	return (philos);
}

t_args  set_args(char **av)
{
    t_args  args;

    args.philo_amount = (unsigned int)ft_atoi(av[1]);
    // args.times_philosopher_eat = (unsigned int)ft_atoi(av[2]);
    // args.time_to_die = (unsigned long long)ft_atoi(av[3]);
    // args.time_to_eat = (unsigned long long)ft_atoi(av[4]);
    // args.time_to_sleep = (unsigned long long)ft_atoi(av[5]);
    return (args);
}

void	*philo_routine(void *philo)
{
	t_philo *new_philo = (t_philo*)philo;
 	//while (1)
 	//{
 		printf("Philo id %d\n", (int)new_philo->id);
		printf("Philo sleep %d\n", (int)new_philo->sleeping);

 	//}
	 return NULL;
}

int main(int ac , char **av)
{
	int		i;
	int		err;
    t_args  args;
	t_philo	*philos;

	i = 0;
    // if (ac == 5)
    // {
        args = set_args(av);
        philos = create_philos(args);
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
  //  }
    // else
    // {
    //     write(2, "Philo should takes 5 arguments:\n1: number_of_philosophers\n2: time_to_die\n3: time_to_eat\n4: time_to_sleep\n5: number_of_times_each_philosopher_must_eat");
    // }
}