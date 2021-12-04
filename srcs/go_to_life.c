/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:06:13 by viporten          #+#    #+#             */
/*   Updated: 2021/12/04 02:55:35 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
		write_status(moi, " died\n");
		pthread_mutex_unlock(moi->are_u_alive);
		pthread_mutex_unlock(moi->fork_l);
		pthread_mutex_unlock(moi->fork_r);
		return ;
	}
	pthread_mutex_unlock(moi->are_u_alive);
	write_status(moi, " has taken a fork\n");
	write_status(moi, " has taken a fork\n");
	write_status(moi, " is eating\n");
	sleep_time(moi, moi->inf.time_eat);
	pthread_mutex_unlock(moi->fork_l);
	pthread_mutex_unlock(moi->fork_r);
}

void	*routine(void *x)
{
	int		i;
	t_philo	*moi;

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

void	*solo(void *x)
{
	t_philo	*moi;

	moi = (t_philo *)x;
	write_status(moi, " has taken a fork\n");
	while (1)
	{
		usleep(50);
		pthread_mutex_lock(moi->are_u_alive);
		if (check_death(moi) == 1)
		{
			*(moi->dead) = 1;
			write_status(moi, " is died\n");
			pthread_mutex_unlock(moi->are_u_alive);
			return (NULL);
		}
		pthread_mutex_unlock(moi->are_u_alive);
	}
}

void	life_become_reality(pthread_t *life, t_philo *philo, t_inf *inf)
{
	int	i;

	i = 0;
	if (inf->nbr_p == 1)
		pthread_create(&life[i], NULL, &solo, &philo[i]);
	else
	{
		while (i < inf->nbr_p)
		{
			pthread_create(&life[i], NULL, &routine, &philo[i]);
			i++;
		}
	}
	i = 0;
	while (i < inf->nbr_p)
	{
		pthread_join(life[i], NULL);
		i++;
	}
	i = 0;
	destroy_all(philo, inf);
	free(life);
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
	if (life == NULL)
		return (destroy_all(philo, inf));
	init_timeval(&philo);
	life_become_reality(life, philo, inf);
	return (0);
}
