/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:52:11 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/30 17:21:27 by jdomingu         ###   ########.fr       */
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
	int				total_meals;
	int				t0;
	pthread_mutex_t	write_mtx;
	int				meals_eaten;
	pthread_mutex_t	eaten_mtx;
	int				philo_death;
	pthread_mutex_t	death_mtx;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		fork_mtx;
	int					last_meal;
	int					num_meals;
	t_data				*data;
	t_philo				*next;
}	t_philo;

long	ft_atoi_long(char *str);
int		valid_args(int ac, char **av);
int		init_data(int ac, char **av, t_data *data);
int		philo_died(t_data *data);
void	*routine(void *philo_data);
int		meals_eaten(t_data *data);
int		check_death(t_philo *philo);
void	print_status(t_philo *philo, char *str);
void	ft_sleep(int ms);
int		get_actual_time(void);
void	free_all(t_data *data);
void	free_threads(t_data *data);
void	free_all_mtx(t_data *data);
void	free_philo_mtx(t_data *data);
void	free_mtx(t_data *data, char option);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
void	ft_lstclear_philos(t_philo **philo);

#endif
