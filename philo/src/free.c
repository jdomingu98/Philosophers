/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 03:27:38 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/06 04:09:30 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_mtx(t_data *data, char option)
{
	pthread_mutex_destroy(&data->message_mtx);
	if (option == 'a')
		pthread_mutex_destroy(&data->philo_death_mtx);
	if (option == 'a' || option == 'd')
		pthread_mutex_destroy(&data->eaten_mtx);
}

void	free_philo_mtx(t_data *data, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		pthread_mutex_destroy(&data->philos[i].fork_mtx);
		i++;
	}
	pthread_mutex_destroy(&data->philos[i].fork_mtx);
}

void	free_all_mtx(t_data *data)
{
	free_mtx(data, 'a');
	free_philo_mtx(data, data->nphilos);
}

void	free_threads(t_philo *philos, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
		pthread_detach(philos[i++].thread);
}

void	free_all(t_data *data)
{
	free_all_mtx(data);
	free(data->philos);
	free(data);
}
