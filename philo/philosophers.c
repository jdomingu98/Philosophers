/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:37:10 by jdomingu          #+#    #+#             */
/*   Updated: 2023/02/23 18:21:13 by jdomingu         ###   ########.fr       */
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

static int	fill_philo_data(t_philos *philo, int total_philos)
{
	int			i;
	t_philos *aux;

	aux = philo;
	i = 1;
	while (i <= total_philos)
	{
		aux = ft_calloc(sizeof(t_philos), 1);
		if (!aux)
			return (1);
		aux->philo_name = i;
		aux->last_eat = 0;
		aux->num_eats = 0;
		aux->state = THINKING;
		//aux->fork = ??;
		//aux->thread = ??;
		aux = aux->next_philo;
	}
	return (0);
}

static int	fill_data(char *arg, t_data *data, int idx)
{
	int nbr;

	nbr = ft_atoi(arg);
	if (nbr < 0)
		return (1);
	if (idx == 1)
	{
		data->nbr_philos = nbr;
		if (fill_philo_data(data->philo, data->nbr_philos))
			return (1);
	}
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || init_values(&data, argc, argv))
		return (-1)
	while (1)
	{
		
	}
	free_all_data(&data);
	return (0);
}
