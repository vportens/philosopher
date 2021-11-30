/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:27:48 by laclide           #+#    #+#             */
/*   Updated: 2021/11/30 13:45:37 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

pthread_mutex_t	*init_a_fork(void)
{
	pthread_mutex_t *fork;
	
	fork = malloc(sizeof(pthread_mutex_t));
	if (fork == NULL)
		return (NULL);
	if (pthread_mutex_init(fork, 0) != 0)
	{
		free(fork);
		return (NULL);
	}
	return (fork);
}

int	init_timeval(t_philo **start)
{
	struct timeval		tv;
	unsigned long long	time_start;
	t_philo				*cur;
	int					i;
	int					to;

	cur = *start;
	i = 0;
	to = cur[i].inf.nbr_p;
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	time_start = ((tv.tv_sec * 1000) + (tv.tv_usec/1000));
	while (i < to)
	{
		cur[i].time_start = time_start;
		i++;
	}
	return (0);
}

int	*init_lock(void)
{
	int	*new;

	new = malloc(sizeof(int));
	if (new == NULL)
		return (NULL);
	*new = 0;
	return (new);
}

int	init_philo(t_philo **start, t_inf *inf, pthread_mutex_t *out, int *dead)
{
	t_philo *cur;
	int		i;

	cur = *start;
	i = 0;
	while (i < inf->nbr_p)
	{
		cur[i].inf = *inf;
		cur[i].id = i;
		cur[i].lock_r = init_lock();
		cur[i].fork_r = init_a_fork();
		if (cur[i].fork_r == NULL)
		{
			destroy_all_mutex(start, i);
			pthread_mutex_destroy(out);
			return (free_defore_init_fork(start, out, dead, 70));
		}
		cur[i].out = out;
		cur[i].dead = dead;
		if (i != 0)
		{
			cur[i].fork_l = cur[i - 1].fork_r;
			cur[i].lock_l = cur[i - 1].lock_r;
		}
		if (i == inf->nbr_p - 1 && inf->nbr_p - 1 != 0)
		{
			cur[0].fork_l = cur[i].fork_r;
			cur[0].lock_l = cur[i].lock_r;
		}
		i++;
	}
	return (0);
}

int	init_and_deal_fork_to_philo(t_philo **start, t_inf *inf)
{
	t_philo 		*cur;
	pthread_mutex_t *out;
	int				*dead;
	int				i;

	cur = *start;
	out = malloc(sizeof(pthread_mutex_t));
	if (out == NULL)
		return (free_defore_init_fork(start, NULL, NULL, 50));
	dead = malloc(sizeof(int));
	if (dead == NULL)
		return (free_defore_init_fork(start, out, NULL, 50));
	*dead = 0;
	i = 0;
	if (pthread_mutex_init(out, 0) != 0)
		return (free_defore_init_fork(start, out, dead, 70));
	if (init_philo(start, inf, out, dead) != 0)
		return (70);
	if (init_timeval(start) == -1)
	{
		destroy_all_mutex(start, inf->nbr_p);
		pthread_mutex_destroy(out);
		return (free_defore_init_fork(start, out, dead, 10));
	}
	return (0);
}

