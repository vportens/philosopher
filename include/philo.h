#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/includes/libft.h"

typedef struct	s_philo		t_philo;

typedef struct	s_inf
{
	int	nbr_p;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	time_time_eat;
	int	time_reset;
}				t_inf;

struct	s_philo
{
	int 	id;
	int		*dead;
	t_inf	inf;
	unsigned long long	time_start;
	unsigned long long	time_life;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*out;
};

int	go_to_life(t_inf *inf);

int	init_and_deal_fork_to_philo(t_philo **start, t_inf *inf);

void	destroy_all_mutex(t_philo **start, int nbr_to_destroy);
int	free_defore_init_fork(t_philo **start, pthread_mutex_t *out, int *dead, int ret);

int	check_death(t_philo *moi);
unsigned long long	get_time(void);
void	write_status(t_philo *moi, int status);

#endif
