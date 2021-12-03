/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_fonction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 00:03:31 by viporten          #+#    #+#             */
/*   Updated: 2021/12/04 00:04:05 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_time(t_philo *moi, int time_usleep)
{
	int					t;
	unsigned long long	time_start;

	t = 0;
	time_start = get_time();
	while (get_time() - time_start < (unsigned long long)time_usleep)
	{
		usleep(50);
		pthread_mutex_lock(moi->are_u_alive);
		if (*(moi->dead) == 1)
		{
			pthread_mutex_unlock(moi->are_u_alive);
			return (1);
		}
		if (check_death(moi) == 1)
		{
			*(moi->dead) = 1;
			write_status(moi, "is dead\n");
			pthread_mutex_unlock(moi->are_u_alive);
			return (1);
		}
		pthread_mutex_unlock(moi->are_u_alive);
	}
	return (0);
}
