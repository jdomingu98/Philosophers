/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:25:27 by jdomingu          #+#    #+#             */
/*   Updated: 2023/02/25 13:25:29 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all_data(t_data *data)
{
	t_philos *aux;

	while(data->philo)
	{
		aux = data->philo->next_philo;
		//eliminar fork y thread??
		free(data->philo);
		data->philo = aux;
	}
}
