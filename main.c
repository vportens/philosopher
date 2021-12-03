/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:27:57 by viporten          #+#    #+#             */
/*   Updated: 2021/12/03 23:35:40 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	parsing(int ac, char **av, t_inf *inf)
{
	if (!ft_true_atoi(&(inf->nbr_p), av[1]) || inf->nbr_p <= 0)
		return (0);
	if (!ft_true_atoi(&(inf->time_die), av[2]) || inf->time_die <= 0)
		return (0);
	if (!ft_true_atoi(&(inf->time_eat), av[3]) || inf->time_eat <= 0)
		return (0);
	if (!ft_true_atoi(&(inf->time_sleep), av[4]) || inf->time_sleep <= 0)
		return (0);
	if (ac == 6)
		if (!ft_true_atoi(&(inf->time_time_eat), av[5])
			|| inf->time_time_eat <= 0)
			return (0);
	return (1);
}

void	init_inf(t_inf *inf)
{
	inf->nbr_p = 0;
	inf->time_die = 0;
	inf->time_eat = 0;
	inf->time_sleep = 0;
	inf->time_time_eat = 0;
	inf->time_reset = 0;
}

int	main(int ac, char **av)
{
	t_inf	inf;

	init_inf(&inf);
	if (ac != 5 && ac != 6)
	{
		write(2, "bad nbr of arg\n", 15);
		return (1);
	}
	if (!parsing(ac, av, &inf))
	{
		write(2, "bad arg\n", 8);
		return (1);
	}
	go_to_life(&inf);
	return (0);
}
