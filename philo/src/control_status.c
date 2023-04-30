/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 03:27:33 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/30 17:20:46 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(int ms)
{
	int	initial;

	initial = get_actual_time();
	while (get_actual_time() - initial < ms)
		usleep(50);
}

void	print_status(t_philo *philo, char *str)
{
	if (meals_eaten(philo->data) || philo_died(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_mtx);
	printf("%d	%d %s\n", get_actual_time() - philo->data->t0,
		philo->id, str);
	pthread_mutex_unlock(&philo->data->write_mtx);
}

int	meals_eaten(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->eaten_mtx);
	if (data->meals_eaten == data->nphilos)
		res = 1;
	return (pthread_mutex_unlock(&data->eaten_mtx), res);
}

int	check_death(t_philo *philo)
{
	if (philo->last_meal + philo->data->time_die < get_actual_time())
	{
		print_status(philo, "died");
		pthread_mutex_lock(&philo->data->death_mtx);
		philo->data->philo_death = 1;
		pthread_mutex_unlock(&philo->data->death_mtx);
		return (1);
	}
	return (0);
}
