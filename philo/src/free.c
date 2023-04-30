/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 03:27:38 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/30 17:20:54 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_mtx(t_data *data, char option)
{
	pthread_mutex_destroy(&data->write_mtx);
	if (option == 'a')
		pthread_mutex_destroy(&data->death_mtx);
	if (option == 'a' || option == 'd')
		pthread_mutex_destroy(&data->eaten_mtx);
}

void	free_philo_mtx(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philos;
	while (tmp)
	{
		pthread_mutex_destroy(&tmp->fork_mtx);
		tmp = tmp->next;
	}
}

void	free_all_mtx(t_data *data)
{
	free_mtx(data, 'a');
	free_philo_mtx(data);
}

void	free_threads(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philos;
	while (tmp)
	{
		if (tmp->thread)
			pthread_detach(tmp->thread);
		tmp = tmp->next;
	}
}

void	free_all(t_data *data)
{
	free_all_mtx(data);
	ft_lstclear_philos(&data->philos);
	free(data->philos);
	free(data);
}
