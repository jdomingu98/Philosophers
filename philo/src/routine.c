/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:50:55 by jdomingu          #+#    #+#             */
/*   Updated: 2023/02/25 17:07:42 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/*
	printeame_esta(t_philo *p, char action)
		printea el mensaje segun action
	 		- f: ha codigo un tenedor
	 		- d: esta muerto
	 		- e: esta comiendo
	 		- s: se fue a mimir
			- t: pensando en la vida
	za_warudo(int time)
		para el proceso time ms (usleep custom)
*/
static void	go_eat(t_philos *p)
{
	int	left_index;

	left_index = p->philo_name - 1;
	if (left_index == 0)
		left_index = p->data_rewind->nbr_philos;
	pthread_mutex_lock(&philo->right_fork);
	printeame_esta(p, 'f');
	if (p->data_rewind->nbr_philos == 1)
	{
		za_warudo(p->data_rewind->die_time);
		printeame_esta(p, 'd');
		p->state = DEAD;
	}
	pthread_mutex_lock(&p->data_rewind->philo[left_index]->right_fork);
	printeame_esta(p, 'f');
	p->state = EATING;
	p->last_eat = actual_time(p->data->rewind->start_time);
	p->num_eats++;
	printeame_esta(p, 'e');
	za_warudo(p->data_rewind->eat_time);
	pthread_mutex_unlock(&p->right_fork);
	pthread_mutex_unlock(&p->data_rewind->philo[left_index]->right_fork);
}

void *routine(void *philo_data)
{
	t_philos	*p;

	p = (t_philo *) philo_data;
	//Paramos a los pares un instante para evitar data races
	//if (p->philo_name % 2 == 0)
	//	usleep(1000);
	while (p->state != DEAD)
	{
		go_eat(p);
		if (p->data_rewind->total_eats == p->num_eats)
		{
			p->state = DONE;
			break ;
		}
		p->state = SLEEPING;
		printeame_esta(p, 's');
		za_warudo(p->data_rewind->sleep_time);
		p->state = THINKING;
		printeame_esta(p, 't');
	}
	return (NULL);
}
