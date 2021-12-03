/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:06:13 by viporten          #+#    #+#             */
/*   Updated: 2021/12/03 22:24:09 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	sleep_time(t_philo *moi, int time_usleep)
{
	int	t;
	unsigned long long	 time_start;

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

void	eat_one(t_philo *moi)
{
	pthread_mutex_lock(moi->fork_r);
	pthread_mutex_lock(moi->fork_l);
	pthread_mutex_lock(moi->are_u_alive);
	if (*(moi->dead) == 1)
	{
		pthread_mutex_unlock(moi->are_u_alive);
		pthread_mutex_unlock(moi->fork_l);
		pthread_mutex_unlock(moi->fork_r);
		return ;
	}
	if (check_death(moi) == 1)
	{
		*(moi->dead) = 1;
		write_status(moi, " is dead\n");
		pthread_mutex_unlock(moi->are_u_alive);
		pthread_mutex_unlock(moi->fork_l);
		pthread_mutex_unlock(moi->fork_r);
		return ;
	}
	pthread_mutex_unlock(moi->are_u_alive);
	write_status(moi, " is eating\n");
	sleep_time(moi, moi->inf.time_eat);
	pthread_mutex_unlock(moi->fork_l);
	pthread_mutex_unlock(moi->fork_r);
}



void	*routine(void *x)
{
	int					i;
	t_philo *moi;

	i = 0;
	moi = (t_philo *)x;
	if (moi->id % 2 == 1)
		usleep(10000);
	while (1)
	{
		if (check_someone_dead(moi) == 1)
			return (NULL);
		eat_one(moi);
		i++;
		moi->time_life = get_time();
		if (check_someone_dead(moi) == 1)
			return (NULL);
		if (i == moi->inf.time_time_eat)
			return (NULL);
		write_status(moi, " is sleeping\n");
		sleep_time(moi, moi->inf.time_sleep);
		if (check_someone_dead(moi) == 1)
			return (NULL);
		write_status(moi, " is thinking\n");
	}
	return (NULL);
}

int	go_to_life(t_inf *inf)
{
	t_philo			*philo;
	int				ret;
	int				i;
	pthread_t		*life;
	
	i = 0;
	philo = malloc(sizeof(t_philo) * (inf->nbr_p));
	if (philo == NULL)
		return (50);
	ret = init_and_deal_fork_to_philo(&philo, inf);
	if (ret != 0)
		return (ret);
	life = malloc(sizeof(pthread_t) * inf->nbr_p);
	init_timeval(&philo);
	while (i < inf->nbr_p)
	{
		pthread_create(&life[i], NULL, &routine, &philo[i]);	
		i++;
	}
	i = 0;
	while (i < inf->nbr_p)
	{
		pthread_join(life[i], NULL);
		i++;
	}
	i = 0;
	
	while (i < inf->nbr_p)
	{
		pthread_mutex_destroy(philo[i].fork_r);
		i++;
	}
	pthread_mutex_destroy((philo[i - 1].out));
	pthread_mutex_destroy((philo[i - 1].are_u_alive));
	return (0);
}
