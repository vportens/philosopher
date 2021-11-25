#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include "../libft/includes/libft.h"

typedef struct	s_inf
{
	int	nbr_p;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	time_time_eat;
}				t_inf;

typedef struct	s_philo
{
	int 	id;
	t_inf	inf;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*out;

}				t_philo;

char	*go_to_life(t_inf *inf);

#endif