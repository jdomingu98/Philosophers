#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				nbr_meals;
	pthread_t		thread;
	pthread_mutex_t	fork_mtx;
	pthread_mutex_t	meals_mtx; //inutil??
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nphilos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_must_eat;
	int				t0;
	int				must_eat_count;
	int				philo_death;
	pthread_mutex_t	message_mtx;
	pthread_mutex_t	eaten_mtx;
	pthread_mutex_t philo_death_mtx;
	t_philo			*philos;
}	t_data;



#endif