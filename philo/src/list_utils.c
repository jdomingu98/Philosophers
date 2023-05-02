/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:21:04 by jdomingu          #+#    #+#             */
/*   Updated: 2023/04/30 17:21:06 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*p;

	if (!*lst)
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

void	ft_lstclear_philos(t_philo **philo)
{
	t_philo	*next;

	while (*philo)
	{
		next = (*philo)->next;
		free(philo);
		*philo = next;
	}
}
