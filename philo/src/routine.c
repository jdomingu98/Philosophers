/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 03:28:02 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/06 04:09:52 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_died(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->philo_death_mtx);
	if (data->philo_death)
		res = 1;
	return (pthread_mutex_unlock(&data->philo_death_mtx), res);
}

static void	check_if_total_meals_eaten(t_philo *philo)
{
	if (philo->nbr_meals == philo->data->nbr_must_eat)
	{
		pthread_mutex_lock(&philo->data->eaten_mtx);
		philo->data->must_eat_count++;
		pthread_mutex_unlock(&philo->data->eaten_mtx);
	}
}

static void	init_odd_philos_routine(t_philo *philo)
{
	if (philo->id % 2)
		ft_sleep(5);
	philo->last_meal = get_actual_time();
}

static void	taking_forks(t_philo *philo, t_data *data)
{
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_mtx);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&data->philos[philo->id % data->nphilos].fork_mtx);
}

void	*routine(void *philo_data)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) philo_data;
	data = philo->data;
	init_odd_philos_routine(philo);
	while (!meals_eaten(data) && !philo_died(data))
	{
		taking_forks(philo, data);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->meals_mtx);
		philo->last_meal = get_actual_time();
		pthread_mutex_unlock(&philo->meals_mtx);
		ft_sleep(data->time_eat);
		philo->nbr_meals++;
		check_if_total_meals_eaten(philo);
		pthread_mutex_unlock(&philo->fork_mtx);
		pthread_mutex_unlock(&data->philos[philo->id % data->nphilos].fork_mtx);
		print_status(philo, "is sleeping");
		ft_sleep(data->time_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
