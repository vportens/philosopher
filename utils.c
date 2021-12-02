/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:43:34 by viporten          #+#    #+#             */
/*   Updated: 2021/12/02 20:28:12 by viporten         ###   ########.fr       */
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
	if (ret > moi->inf.time_die)
		return (1);
	return (0);

}

unsigned long long	get_time(void)
{
	struct timeval	tv;
	unsigned long long		ret;

	gettimeofday(&tv, NULL);
	ret = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (ret);
}

void	write_status(t_philo *moi, char *text)
{
	pthread_mutex_lock(moi->out);
	printf("%llu id : %d %s", get_time() - moi->time_start, moi->id, text);
	pthread_mutex_unlock(moi->out);
}

void	write_shit(char *t, t_philo *moi)
{
	char	*str;

	pthread_mutex_lock(moi->out);
	str = ft_itoa((int)(get_time() - moi->time_start));
	write(1, str, ft_strlen(str)); 
	write(1, t, ft_strlen(t));
	pthread_mutex_unlock(moi->out);

}