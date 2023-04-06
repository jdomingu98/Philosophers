#include "philosophers.h"

//Repasar gettimeofday
int	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(int ms)
{
	int	initial;

	initial = get_actual_time();
	while (get_actual_time() - initial < ms)
		usleep(50);
}

void	print_status(t_philo *philo, char *str)
{
	if (meals_eaten(philo->data) || philo_died(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->message_mtx);
	printf("[%d]	%d %s\n", get_actual_time() - philo->data->t0, philo->id, str);
	pthread_mutex_unlock(&philo->data->message_mtx);
}

//Uso de philo_death_mtx innecesario creo
int	check_death(t_philo philo)
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