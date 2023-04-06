#include "philosophers.h"

int	meals_eaten(t_data *data)
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

void	*routine(void *philo_data)
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