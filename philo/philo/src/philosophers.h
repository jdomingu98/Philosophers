/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:37:58 by jdomingu          #+#    #+#             */
/*   Updated: 2023/02/25 18:37:37 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h> 

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FORKING,
	DONE
}	t_state;

typedef struct s_philos
{
	int				philo_name;
	int				last_eat;
	int				num_eats;
	t_state			state;
	pthread_mutex_t	right_fork;
	pthread_t		thread;
	t_data			*data_rewind;
}					t_philos;

typedef struct s_data
{
	int				nbr_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				total_eats;
	int				start_time;
	int				someone_die;
	pthread_mutex_t	message_mutex;
	t_philos		*philo;
}					t_data;

int		ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);
void	free_all_data(t_data *data);
void	*routine(void *philo_data);

#endif
