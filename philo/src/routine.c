/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 03:28:02 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/30 17:21:34 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_died(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->death_mtx);
	if (data->philo_death)
		res = 1;
	return (pthread_mutex_unlock(&data->death_mtx), res);
}

static void	check_if_total_meals_eaten(t_philo *philo, t_data *data)
{
	if (philo->num_meals == data->total_meals)
	{
		pthread_mutex_lock(&data->eaten_mtx);
		data->meals_eaten++;
		pthread_mutex_unlock(&data->eaten_mtx);
	}
}

static void	philo_routine(t_data *data, t_philo *philo, pthread_mutex_t *f1,
			pthread_mutex_t *f2)
{
	while (!meals_eaten(data) && !philo_died(data))
	{
		pthread_mutex_lock(f1);
		print_status(philo, "has taken a fork");
		if (f1 == f2)
		{
			pthread_mutex_unlock(f1);
			break ;
		}
		pthread_mutex_lock(f2);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal = get_actual_time();
		ft_sleep(data->time_eat);
		philo->num_meals++;
		check_if_total_meals_eaten(philo, data);
		pthread_mutex_unlock(f1);
		pthread_mutex_unlock(f2);
		print_status(philo, "is sleeping");
		ft_sleep(data->time_sleep);
		print_status(philo, "is thinking");
	}
}

void	*routine(void *philo_data)
{
	t_philo	*philo;
	t_data	*data;
	t_philo	*next_philo;

	philo = (t_philo *) philo_data;
	data = philo->data;
	if (!philo->next)
		next_philo = data->philos;
	else
		next_philo = philo->next;
	if (philo->id % 2)
	{
		ft_sleep(5);
		philo->last_meal = get_actual_time();
		philo_routine(data, philo, &philo->fork_mtx, &next_philo->fork_mtx);
	}
	else
	{
		philo->last_meal = get_actual_time();
		philo_routine(data, philo, &next_philo->fork_mtx, &philo->fork_mtx);
	}
	return (NULL);
}
