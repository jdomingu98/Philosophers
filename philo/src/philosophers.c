/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:52:21 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/06 02:34:01 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_atoi_long(char *str)
{
	long	nbr;
	int		i;
	int		sign;

	nbr = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

static int	is_positive_int_in_range(char *str, int av_idx)
{
	long	nbr;
	int		nbr_condition;

	nbr = ft_atoi_long(str);
	nbr_condition = nbr >= 0;
	if (av_idx == 1)
		nbr_condition = nbr > 0;
	return (nbr_condition && nbr <= INT_MAX);
}

static int	valid_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!is_positive_int_in_range(av[i], i))
			return (0);
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

static void	free_mtx(t_data *data, char option)
{
	pthread_mutex_destroy(&data->message_mtx);
	if (option == 'a')
		pthread_mutex_destroy(&data->philo_death_mtx);
	if (option == 'a' || option == 'd')
		pthread_mutex_destroy(&data->eaten_mtx);
}

static void	free_philo_mtx(t_data *data, int idx, char option)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		pthread_mutex_destroy(&data->philos[i].fork_mtx);
		pthread_mutex_destroy(&data->philos[i].meals_mtx);
		i++;
	}
	if (option == 'a' || option == 'm')
		pthread_mutex_destroy(&data->philos[i].fork_mtx);
	if (option == 'a')
		pthread_mutex_destroy(&data->philos[i].meals_mtx);
}

static void	free_all_mtx(t_data *data)
{
	free_mtx(data, 'a');
	free_philo_mtx(data, data->nphilos, 'a');
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
			return (free_philo_mtx(data, i, 'f'), free_mtx(data, 'a'), 0);
		if (pthread_mutex_init(&data->philos[i].meals_mtx, NULL))
			return (free_philo_mtx(data, i, 'm'), free_mtx(data, 'a'), 0);
		i++;
	}
	return (1);
}

//Repasar gettimeofday
static int	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	free_threads(t_philo *philos, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
		pthread_detach(philos[i++].thread);
}

static void	ft_sleep(int ms)
{
	int	initial;

	initial = get_actual_time();
	while (get_actual_time() - initial < ms)
		usleep(50);
}

static int	meals_eaten(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->eaten_mtx);
	if (data->nbr_must_eat == 0 || data->must_eat_count == data->nphilos)
		res = 1;
	return (pthread_mutex_unlock(&data->eaten_mtx), res);
}

static int	philo_died(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->philo_death_mtx);
	if (data->philo_death)
		res = 1;
	return (pthread_mutex_unlock(&data->philo_death_mtx), res);
}

static void	print_status(t_philo *philo, char *str)
{
	if (meals_eaten(philo->data) || philo_died(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->message_mtx);
	printf("[%d]	%d %s\n", get_actual_time() - philo->data->t0, philo->id, str);
	pthread_mutex_unlock(&philo->data->message_mtx);
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

static void	*routine(void *philo_data)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) philo_data;
	data = philo->data;
	init_odd_philos_routine(philo);
	while (!meals_eaten(data) && !philo_died(data))
	{
		pthread_mutex_lock(&philo->fork_mtx);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&data->philos[philo->id % data->nphilos].fork_mtx);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->meals_mtx);
		print_status(philo, "is eating");
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

static int	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	memset(data, 0, sizeof(t_data));
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

//Uso de philo_death_mtx innecesario creo
static int	check_death(t_philo philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo.meals_mtx);
	if (philo.last_meal + philo.data->time_die < get_actual_time())
	{
		print_status(&philo, "died");
		pthread_mutex_lock(&philo.data->philo_death_mtx);
		philo.data->philo_death = 1;
		pthread_mutex_unlock(&philo.data->philo_death_mtx);
		res = 1;
	}
	return (pthread_mutex_unlock(&philo.meals_mtx), res);
}

//invalid pointer
static void	free_all(t_data data)
{
	free_all_mtx(&data);
	free(data.philos);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (-1);
	if (!valid_args(argc, argv))
		return (-1);
	if (!init_data(argc, argv, &data))
		return (-1);
	while (i < data.nphilos)
	{
		if (check_death(data.philos[i]) || meals_eaten(&data))
			break ;
		i++;
	}
	i = 0;
	while (i < data.nphilos)
		pthread_join(data.philos[i++].thread, NULL);
	if (data.nbr_must_eat == 0
		|| (!data.philo_death && data.must_eat_count == data.nphilos))
		printf("All philos have eaten %d times\n", data.nbr_must_eat);
	return (free_all(data), 0);
}
