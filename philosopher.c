/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/09/13 14:37:38 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

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
	}
	else
		error(ARGS_FAIL, NULL);
}
