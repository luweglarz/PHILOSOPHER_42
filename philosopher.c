/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/03 19:31:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;

	if (ac == 6)
	{
		args = set_args(av);
		philos = create_philos(&args);
		create_threads(args, philos);
	}
	else
		error(ARGS_FAIL, NULL);
}
