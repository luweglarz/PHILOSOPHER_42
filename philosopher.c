/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:59:18 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/30 15:09:23 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosopher.h"

int main(int ac , char **av)
{
    int     forks;

    if (ac == 5)
    {
        forks = ft_atoi(av[1]);


    }
    else
    {
        dprintf(2, "Philo should takes 5 arguments:\n1: number_of_philosophers\n2: time_to_die\n3: time_to_eat\n4: time_to_sleep\n5: number_of_times_each_philosopher_must_eat");
    }
}