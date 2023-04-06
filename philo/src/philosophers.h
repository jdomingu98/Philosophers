/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:52:11 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/06 04:09:40 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo	t_philo;

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
	pthread_mutex_t	philo_death_mtx;
	t_philo			*philos;
}	t_data;

//meals_mtx es inutil creo
typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				nbr_meals;
	pthread_t		thread;
	pthread_mutex_t	fork_mtx;
	pthread_mutex_t	meals_mtx;
	t_data			*data;
}	t_philo;

long	ft_atoi_long(char *str);
int		valid_args(int ac, char **av);
int		init_data(int ac, char **av, t_data *data);
int		philo_died(t_data *data);
void	*routine(void *philo_data);
int		meals_eaten(t_data *data);
int		check_death(t_philo philo);
void	print_status(t_philo *philo, char *str);
void	ft_sleep(int ms);
int		get_actual_time(void);
void	free_all(t_data *data);
void	free_threads(t_philo *philos, int idx);
void	free_all_mtx(t_data *data);
void	free_philo_mtx(t_data *data, int idx, char option);
void	free_mtx(t_data *data, char option);

#endif
