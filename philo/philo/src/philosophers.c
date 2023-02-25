/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:37:10 by jdomingu          #+#    #+#             */
/*   Updated: 2023/02/25 16:43:24 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_threads(t_data *data)
{
	int i;

	i = 0;
	while (++i <= data->nbr_philos)
	{
		data->philo[i]->data_rewind = data;
		if (pthread_create(data->philo[i]->thread, NULL, routine, data->philo[i]) != 0)
		{
			free_all_data(data);
			return (1);
		}
	}
	i = -1;
	while (++i < data->nbr_philos)
		phtread_join(data->philo[i]->thread, NULL);
	return (0);
}

static void	fill_philo_data(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->total_philos)
	{
		data->philo[i]->philo_name = i;
		data->philo[i]->state = THINKING;
		pthread_mutex_init(data->philo[i]->right_fork, NULL);
	}
}

static int	fill_data(char *arg, t_data *data, int idx)
{
	int nbr;

	nbr = ft_atoi(arg);
	if (nbr <= 0)
		return (1);
	if (idx == 1)
		data->nbr_philos = nbr;
	else if (idx == 2)
		data->die_time = nbr;
	else if (idx == 3)
		data->eat_time = nbr;
	else if (idx == 4)
		data->sleep_time = nbr;
	else if (idx == 5)
		data->total_eats = nbr;
	return (0);
}

static int	init_values(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (fill_data(argv[i], data, i))
			return (1);
	}
	if (argc == 5)
		data->total_eats = -1;
	data->philo = ft_calloc(data->nbr_philos * sizeof(t_philos));
	if (!data->philo)
		return (1);
	fill_philo_data(data);
	return(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || init_values(&data, argc, argv))
		return (-1)
	if (init_threads(&data))
		return (-1);
	free_all_data(&data);
	return (0);
}
