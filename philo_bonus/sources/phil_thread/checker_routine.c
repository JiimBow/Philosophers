/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:54:21 by jodone            #+#    #+#             */
/*   Updated: 2026/02/26 15:24:40 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	*die_checker_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	sem_wait(philo->data->philo_die);
	sem_wait(philo->data->sem_data);
	philo->data->stop = 1;
	sem_post(philo->data->sem_data);
	sem_post(philo->data->philo_die);
	return (NULL);
}

static int	check_philo_die(t_philo *philo)
{
	size_t	die_timestamp;

	die_timestamp = get_timestamp(philo->data);
	if (die_timestamp - philo->last_meal >= philo->data->starve_time)
	{
		usleep(500);
		sem_wait(philo->data->sem_data);
		if (philo->data->stop == 0)
		{
			printf("%lu %d died\n", die_timestamp, philo->id + 1);
			sem_post(philo->data->monitor_check);
			philo->data->stop = 1;
		}
		sem_post(philo->data->sem_data);
		return (1);
	}
	return (0);
}

void	checker_routine(t_philo *philo)
{
	while (1)
	{
		if (check_philo_die(philo) == 1)
			break ;
		if (philo->data->eat_nb != -1)
		{
			if (philo->nb_meals == philo->data->eat_nb)
			{
				sem_wait(philo->data->sem_data);
				philo->data->stop = 1;
				sem_post(philo->data->sem_data);
				break ;
			}
		}
		usleep(50);
	}
}
