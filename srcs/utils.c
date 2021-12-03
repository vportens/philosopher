/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:43:34 by viporten          #+#    #+#             */
/*   Updated: 2021/12/04 00:08:18 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"

int	check_death(t_philo *moi)
{
	struct timeval	tv;
	long			ret;

	gettimeofday(&tv, NULL);
	ret = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - moi->time_life;
	if (ret >= moi->inf.time_die)
		return (1);
	return (0);
}

int	check_someone_dead(t_philo *moi)
{
	pthread_mutex_lock(moi->are_u_alive);
	if (*(moi->dead) == 1)
	{
		pthread_mutex_unlock(moi->are_u_alive);
		return (1);
	}
	pthread_mutex_unlock(moi->are_u_alive);
	return (0);
}

unsigned long long	get_time(void)
{
	struct timeval		tv;
	unsigned long long	ret;

	gettimeofday(&tv, NULL);
	ret = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (ret);
}

void	write_status(t_philo *moi, char *text)
{
	pthread_mutex_lock(moi->out);
	{
		printf("%llu id : %d %s", get_time()
			- moi->time_start, moi->id + 1, text);
	}
	pthread_mutex_unlock(moi->out);
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
