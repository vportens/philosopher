/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:06:13 by viporten          #+#    #+#             */
/*   Updated: 2021/11/30 15:31:02 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

unsigned long long	update_cur_time(t_philo *moi)
{
	struct timeval	tv;
	unsigned long long	ret;

	gettimeofday(&tv, NULL);
	ret = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - moi->time_life;
	moi->time_manger = moi->time_manger + ret;
	return (ret);
}

unsigned long long	update_start(void)
{
	struct timeval	tv;
	unsigned long long	ret;

	gettimeofday(&tv, NULL);
	ret = (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
	return (ret);
}


void	write_status(t_philo *moi, int status)
{
	char	*str;
	moi->time_life = update_start();
	str = ft_itoa(moi->time_life - moi->time_start);
	write(1, str, ft_strlen(str)); 
	write(1, " id : ", 6);
	write(1, ft_itoa(moi->id), ft_strlen(ft_itoa(moi->id)));
	if (status == 1)
		write(1, " mange\n", 7);
	else if (status == 2)
		write(1, " dort\n", 6);
	else if (status == 3)
		write(1, " pense\n", 7);
	else if (status == 4)
		write(1, " a finit de manger\n", ft_strlen(" a finit de manger\n"));
	else if (status == 5)
		write(1, " meurt\n", 7);
}


void	eat_one(t_philo *moi)
{
	int	t;

	t = 0;
	pthread_mutex_lock(moi->fork_r);
	pthread_mutex_lock(moi->fork_l);
	pthread_mutex_lock(moi->out);
	write_status(moi, 1);
	pthread_mutex_unlock(moi->out);
	while (t < moi->inf.time_eat * 1000)
	{
		if (moi->inf.time_eat * 1000 - t > 400)
			usleep(400);
		else
			usleep((moi->inf.time_eat * 1000 - t));
		t = t + 400;
		if (moi->inf.time_die < (int)update_cur_time(moi))
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

void	eat_two(t_philo *moi)
{
	int	t;

	t = 0;
	pthread_mutex_lock(moi->fork_l);
	pthread_mutex_lock(moi->fork_r);
	pthread_mutex_lock(moi->out);
	write_status(moi, 1);
	pthread_mutex_unlock(moi->out);
	while (t < moi->inf.time_eat * 1000)
	{
		if (moi->inf.time_eat * 1000 - t > 400)
			usleep(400);
		else
			usleep((moi->inf.time_eat * 1000 - t));
		t = t + 400;
		if (moi->inf.time_die < (int)update_cur_time(moi))
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
//	moi->time_start = ((tv.tv_sec * 1000000) + (tv.tv_usec));
	moi->time_life = moi->time_start;
	i = 0;
	while (1)
	{
		if (*(moi->dead) != 0)
			return (0);
		if (moi->id % 2 == 0)
		{
			eat_one(moi);
			i++;
		}
		else
		{
			eat_two(moi);
			i++;
		}
		if (*(moi->dead) == 1)
		{
			pthread_mutex_lock(moi->out);
			write_status(moi, 5);
			pthread_mutex_unlock(moi->out);
			return (0);
		}
		moi->time_life = update_start();
		moi->time_manger = 0;
		if (i == moi->inf.time_time_eat)
		{
			pthread_mutex_lock(moi->out);
			write_status(moi, 4);
			pthread_mutex_unlock(moi->out);
			return (0);
		}
		pthread_mutex_lock(moi->out);
		write_status(moi, 2);
		pthread_mutex_unlock(moi->out);
		usleep(moi->inf.time_sleep);
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
