/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:53 by jdomingu          #+#    #+#             */
/*   Updated: 2023/02/25 17:55:25 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sleep(int ms)
{
	int start_time;

	start_time = actual_time(0);
	while (actual_time(0) - start_time < ms)
		usleep(100);
}

int	actual_time(int time)
{
	struct timeval ti;

	if (gettimeofday(&ti, NULL) == -1)
		return (-1);
	return (ti.tv_sec * 1000 + ti.tv_usec / 1000 - time);
}

void	print_message(t_philos p)
{
	pthread_mutex_lock(&p->data_rewind->message_mutex);
	printf("%d %d ", actual_time(p->data_rewind->start_time), p->philo_name);
	if (p->state == FORKING)
		printf("has taken a fork");
	else if (p->state == EATING)
		printf("is eating");
	else if (p->state == SLEEPING)
		printf("is sleeping");
	else if (p->state == THINKING)
		printf("is thinking");
	else if (p->state == DEAD)
		printf("died");
	pthread_mutex_unlock(&p->data_rewind->message_mutex);
}
