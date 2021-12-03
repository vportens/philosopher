/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:52:51 by laclide           #+#    #+#             */
/*   Updated: 2021/12/03 23:41:11 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_defore_init_fork(t_philo **start, pthread_mutex_t *out,
	int *dead, int ret)
{
	if (out)
		free(out);
	if (dead)
		free(dead);
	if (*start)
		free(*start);
	return (ret);
}

void	destroy_all_mutex(t_philo **start, int nbr_to_destroy)
{
	int		i;
	t_philo	*cur;

	i = 0;
	cur = *start;
	while (i < nbr_to_destroy)
	{
		pthread_mutex_destroy(cur[i].fork_r);
		free(cur[i].fork_r);
		i++;
	}
}

int	destroy_all(t_philo *philo, t_inf *inf)
{
	destroy_all_mutex(&philo, inf->nbr_p);
	pthread_mutex_destroy(philo->out);
	pthread_mutex_destroy(philo->are_u_alive);
	free(philo->dead);
	free(philo->are_u_alive);
	free_defore_init_fork(&philo, philo->out, NULL, 50);
	return (50);
}
