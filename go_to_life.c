/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:06:13 by viporten          #+#    #+#             */
/*   Updated: 2021/11/25 05:58:46 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(pthread_mutex_t **fork, int nbr_to_destroy)
{
	int	i;

	i = 0;
	while (i < nbr_to_destroy)
	{
		pthread_mutex_destroy(fork[i]);
		i++;
	}
}

int	init_mutex(pthread_mutex_t **fork, int to)
{
	int	i;

	i = 0;
	while (i < to)
	{
		if (pthread_mutex_init(fork[i], 0) != 0)
		{
			destroy_all_mutex(fork, i);
			return (0);
		}
		i++;
	}
	fork[i] = NULL;
	return (i);
}

void	init_philo(pthread_mutex_t **fork, t_philo **philo, t_inf *inf, pthread_mutex_t *out)
{
	int	i;

	i = 0;
	while (i < inf->nbr_p)
	{
		philo[i]->inf = *inf;
		philo[i]->id = i;
		philo[i]->out = out;
		philo[i]->fork_r = fork[i];	
		if (i != 0)
			philo[i]->fork_l = fork[i - 1];
		else
			philo[i]->fork_l = fork[inf->nbr_p - 1];
		
		i++;
	}
	philo[i] = NULL;
}

int	init_and_deal_fork_to_philo(pthread_mutex_t **fork, t_philo **philo, t_inf *inf)
{
	pthread_mutex_t	*out;

	out = malloc(sizeof(pthread_mutex_t));
	if (out == NULL)
		return (50);
	if (pthread_mutex_init(out, 0) != 0)
	{
		free(out);
		return (70);
	}
	(*fork) = malloc(sizeof(pthread_mutex_t) * (inf->nbr_p + 1));
	if ((*fork) == NULL)
	{
		pthread_mutex_destroy(out);
		free(out);
		return (50);
	}
	(*philo) = malloc(sizeof(t_philo) * (inf->nbr_p + 1));
	if ((*philo) == NULL)
	{
		pthread_mutex_destroy(out);
		free(out);
		free(*fork);
		return (50);
	}
	if (init_mutex(fork, inf->nbr_p) == 0)
	{
		pthread_mutex_destroy(out);
		free(out);
		free(*fork);
		free(*philo);
		return (70);
	}
	init_philo(fork, philo, inf, out);
	return (0);
}

int	go_to_life(t_inf *inf)
{
	pthread_mutex_t *fork;
	t_philo			*philo;
	int				ret;
	
	ret = init_and_deal_fork_to_philo(&fork, &philo, inf);
	if (ret  != 0)
		return (ret);

}