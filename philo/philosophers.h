/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:37:58 by jdomingu          #+#    #+#             */
/*   Updated: 2023/02/23 18:16:59 by jdomingu         ###   ########.fr       */
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

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;

typedef struct s_philos
{
	int				philo_name;
	int				last_eat;
	int				num_eats;
	t_state			state;
	pthread_mutex_t	fork;
	pthread_t		thread;
	t_philos		*next_philo;
}					t_philos;

typedef struct s_data
{
	int			nbr_philos;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			total_eats;
	t_philos	*philo;
}				t_data;

int		ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);
void	free_all_data(t_data *data);

#endif
