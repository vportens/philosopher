/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:06:13 by viporten          #+#    #+#             */
/*   Updated: 2021/12/01 18:24:19 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	eat_one(t_philo **cur)
{
	int	t;
	t_philo *moi;

	moi = *cur;
	t = 0;
	pthread_mutex_lock(moi->fork_r);
	pthread_mutex_lock(moi->fork_l);
	write_status(moi, 1);
	while (t < moi->inf.time_eat * 1000)
	{
		if (moi->inf.time_eat * 1000 - t > 400)
			usleep(400);
		else
			usleep((moi->inf.time_eat * 1000 - t));
		t = t + 400;
		if (check_death(moi) == 1)
		{
			*(moi->dead) = 1;
			pthread_mutex_unlock(moi->fork_r);
			pthread_mutex_unlock(moi->fork_l);
			return ;
		}
		//check la mort
	}
	pthread_mutex_unlock(moi->fork_r);
	pthread_mutex_unlock(moi->fork_l);
}

void	eat_two(t_philo **cur)
{
	int	t;
	t_philo *moi;

	moi = *cur;
	t = 0;
	pthread_mutex_lock(moi->fork_l);
	pthread_mutex_lock(moi->fork_r);
	write_status(moi, 1);
	while (t < moi->inf.time_eat * 1000)
	{
		if (moi->inf.time_eat * 1000 - t > 400)
		{
			usleep(400);
		}
		else
		{
			usleep((moi->inf.time_eat * 1000 - t));
		}
		t = t + 400;
		if (check_death(moi) == 1)
		{
			*(moi->dead) = 1;
			pthread_mutex_unlock(moi->fork_r);
			pthread_mutex_unlock(moi->fork_l);
			return ;
			
		}
		//check la mort
	}
	pthread_mutex_unlock(moi->fork_l);
	pthread_mutex_unlock(moi->fork_r);
}


int	routine(t_philo *moi)
{
	int					i;
	unsigned long long	cur_time;
	struct timeval		tv;

//	gettimeofday(&tv, NULL);
	//moi->time_start = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	i = 0;
	while (1)
	{
		if (*(moi->dead) != 0)
			return (0);
		if (moi->id % 2 == 0)
		{
			eat_one(&moi);
			i++;
		}
		else
		{
			eat_two(&moi);
			i++;
		}
		if (check_death(moi) == 1)
		{
			(*(moi->dead) = 1);
		}
		if (*(moi->dead) == 1)
		{
			write_status(moi, 5);
			return (0);
		}
		moi->time_life = get_time();
	//	write(2, ft_itoa(moi->time_life), ft_strlen(ft_itoa(moi->time_life)));
		if (i == moi->inf.time_time_eat)
		{
			write_status(moi, 4);
			return (0);
		}
		write_status(moi, 2);
		usleep(moi->inf.time_sleep * 1000);
	}
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
	while (i < inf->nbr_p)
	{
		pthread_create(&life[i], NULL, &routine, &philo[i]);	
		i++;
	}
	i = 0;
/*
	while (1)
	{
		i = 0;
		while (i < inf->nbr_p)
		{
			if (inf->time_die < (int)update_cur_time(&philo[i]))
			{
				write(2, "bite\n\n", 6);
				*(philo[i].dead) = 1;
				break ;
			}
			i++;
		}
		if (*(philo[i].dead) == 1)
			break ;


	}*/
	i = 0;
	while (i < inf->nbr_p)
	{
		pthread_join(life[i], NULL);
		i++;
	}
	
	i = 0;
	while (i < inf->nbr_p)
	{
		write(2, "gate\n", 5);
		printf("philo id : %d\n", philo[i].id);
		i++;
	}
	return (0);

}
