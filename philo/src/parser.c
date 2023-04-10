/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 03:27:44 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/10 12:53:53 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_threads(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->nphilos)
	{
		philo = &data->philos[i];
		if (pthread_create(&data->philos[i].thread, NULL, &routine, philo))
			return (free_threads(data->philos, i), 0);
		i++;
	}
	return (1);
}

static int	init_mtx(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->message_mtx, NULL))
		return (0);
	if (pthread_mutex_init(&data->eaten_mtx, NULL))
		return (free_mtx(data, '\0'), 0);
	if (pthread_mutex_init(&data->philo_death_mtx, NULL))
		return (free_mtx(data, 'd'), 0);
	while (i < data->nphilos)
	{
		if (pthread_mutex_init(&data->philos[i].fork_mtx, NULL))
			return (free_philo_mtx(data, i), free_mtx(data, 'a'), 0);
		i++;
	}
	return (1);
}

static int	init_philo_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(data->nphilos * sizeof(t_philo));
	if (!(data->philos))
		return (0);
	memset(data->philos, 0, sizeof(t_philo));
	while (i < data->nphilos)
	{
		data->philos[i].id = i + 1;
		i++;
	}
	return (1);
}

static void	set_arg_in_data(t_data *data, long nbr, int arg_pos)
{
	if (arg_pos == 1)
		data->nphilos = (int) nbr;
	else if (arg_pos == 2)
		data->time_die = (int) nbr;
	else if (arg_pos == 3)
		data->time_eat = (int) nbr;
	else if (arg_pos == 4)
		data->time_sleep = (int) nbr;
	else if (arg_pos == 5)
		data->nbr_must_eat = (int) nbr;
}

int	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->nbr_must_eat = -1;
	while (++i < ac)
		set_arg_in_data(data, ft_atoi_long(av[i]), i);
	if (!init_philo_data(data))
		return (free(data), 0);
	if (!init_mtx(data))
		return (free(data->philos), free(data), 0);
	i = 0;
	while (i < data->nphilos)
		data->philos[i++].data = data;
	data->t0 = get_actual_time();
	if (!init_threads(data))
		return (free_all_mtx(data), free(data->philos), free(data), 0);
	return (1);
}
