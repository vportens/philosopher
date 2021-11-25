#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
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
	int 	nbr;
	t_inf	inf;


}				t_philo;

#endif