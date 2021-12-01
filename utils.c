/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:43:34 by viporten          #+#    #+#             */
/*   Updated: 2021/12/01 23:54:06 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	write_status(t_philo *moi, int status)
{
	char	*str;

	pthread_mutex_lock(moi->out);
	if (*(moi->dead) == 1 && status != 5)
	{
	pthread_mutex_unlock(moi->out);
	return ;
	}
	str = ft_itoa((int)(get_time() - moi->time_start));
	write(1, str, ft_strlen(str)); 
	write(1, " id : ", 6);
	write(1, ft_itoa(moi->id), ft_strlen(ft_itoa(moi->id)));
	if (status == 0)
		write(1, "\n", 1);
	else
	{
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