/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:52:21 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/30 17:21:21 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_philos_states(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philos;
	while (!check_death(tmp) && !meals_eaten(data))
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			tmp = data->philos;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (-1);
	if (!valid_args(argc, argv))
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	memset(data, 0, sizeof(t_data));
	if (!init_data(argc, argv, data))
		return (-1);
	check_philos_states(data);
	while (data->philos)
	{
		pthread_join(data->philos->thread, NULL);
		pthread_mutex_destroy(&data->philos->fork_mtx);
		data->philos = data->philos->next;
	}
	if (data->total_meals == 0
		|| (!data->philo_death && data->meals_eaten == data->nphilos))
		printf("All philos have eaten %d times\n", data->total_meals);
	return (free_all(data), 0);
}
