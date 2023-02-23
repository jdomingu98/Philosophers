/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:37:58 by jdomingu          #+#    #+#             */
/*   Updated: 2023/02/23 14:22:20 by jdomingu         ###   ########.fr       */
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
	THINKING
} t_state;

typedef struct s_philos
{
	int			philo;
	int			last_eat;
	t_state		state;
	t_philos	*next_philo;
} t_philos;

typedef struct s_data
{
	int			nbr_philos;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			num_eats;
	t_philos	*philo;
} t_data;

void	init_values(t_data *data, int argc, char **argv);

#endif
