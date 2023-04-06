/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:52:21 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/06 04:09:36 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;
	
	i = 0;
	if (argc != 5 && argc != 6)
		return (-1);
	if (!valid_args(argc, argv))
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	memset(data, 0, sizeof(t_data));
	if (!init_data(argc, argv, data))
		return (free(data), -1);
	while (i < data->nphilos)
	{
		if (check_death(data->philos[i]) || meals_eaten(data))
			break ;
		i++;
	}
	i = 0;
	while (i < data->nphilos)
		pthread_join(data->philos[i++].thread, NULL);
	if (data->nbr_must_eat == 0
		|| (!data->philo_death && data->must_eat_count == data->nphilos))
		printf("All philos have eaten %d times\n", data->nbr_must_eat);
	return (free_all(data), 0);
}
