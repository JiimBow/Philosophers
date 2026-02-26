/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:44:04 by jodone            #+#    #+#             */
/*   Updated: 2026/02/26 15:43:30 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	philo_routine(t_philo *philo)
{
	while (philo->nb_meals != philo->data->eat_nb)
	{
		if (thinking_process(philo))
			break ;
		if (picking_fork(philo))
			break ;
		if (eating_process(philo))
			break ;
		if (sleeping_process(philo))
			break ;
	}
}

void	*thread_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->nb_philo == 1)
	{
		printf("%lu %d is thinking\n", get_timestamp(philo->data), philo->id + 1);
		printf("%lu %d has taken a fork\n",
			get_timestamp(philo->data), philo->id + 1);
	}
	else
		philo_routine(philo);
	sem_post(philo->data->first_death);
	return (NULL);
}
