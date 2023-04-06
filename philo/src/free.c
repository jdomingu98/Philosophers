#include "philosophers.h"

void	free_mtx(t_data *data, char option)
{
	pthread_mutex_destroy(&data->message_mtx);
	if (option == 'a')
		pthread_mutex_destroy(&data->philo_death_mtx);
	if (option == 'a' || option == 'd')
		pthread_mutex_destroy(&data->eaten_mtx);
}

void	free_philo_mtx(t_data *data, int idx, char option)
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

void	free_all_mtx(t_data *data)
{
	free_mtx(data, 'a');
	free_philo_mtx(data, data->nphilos, 'a');
}

void	free_threads(t_philo *philos, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
		pthread_detach(philos[i++].thread);
}

//invalid pointer
void	free_all(t_data *data)
{
	free_all_mtx(&data);
	free(data.philos);
    free(data);
}
