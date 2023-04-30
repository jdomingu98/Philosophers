/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 03:27:44 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/30 17:21:14 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_threads(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = -1;
	tmp = data->philos;
	while (++i < data->nphilos)
	{
		if (pthread_mutex_init(&tmp->fork_mtx, NULL))
			return (free_threads(data), free_philo_mtx(data), 0);
		if (pthread_create(&tmp->thread, NULL, &routine, tmp))
			return (free_threads(data), free_philo_mtx(data), 0);
		tmp = tmp->next;
	}
	return (1);
}

static int	init_data_mtx(t_data *data)
{
	if (pthread_mutex_init(&data->write_mtx, NULL))
		return (0);
	if (pthread_mutex_init(&data->eaten_mtx, NULL))
		return (pthread_mutex_destroy(&data->write_mtx), 0);
	if (pthread_mutex_init(&data->death_mtx, NULL))
		return (free_mtx(data, 'd'), 0);
	return (1);
}

static int	init_philo_data(t_data *data)
{
	int			i;
	t_philo		*tmp;

	i = 0;
	while (i < data->nphilos)
	{
		tmp = malloc(sizeof(t_philo));
		if (!tmp)
			return (0);
		memset(tmp, 0, sizeof(t_philo));
		tmp->id = i + 1;
		tmp->data = data;
		tmp->next = NULL;
		ft_lstadd_back(&data->philos, tmp);
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
		data->total_meals = (int) nbr;
}

int	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->total_meals = -1;
	while (++i < ac)
		set_arg_in_data(data, ft_atoi_long(av[i]), i);
	if (!init_data_mtx(data))
		return (free(data), 0);
	if (!init_philo_data(data))
	{
		ft_lstclear_philos(&data->philos);
		free(data->philos);
		free_mtx(data, 'a');
		free(data);
		return (0);
	}
	data->t0 = get_actual_time();
	if (!init_threads(data))
		return (free_all(data), 0);
	return (1);
}
