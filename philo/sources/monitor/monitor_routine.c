/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:42:44 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 15:48:31 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	check_philo_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo[i].thread)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo[i].nb_meals != philo->data->eat_nb)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		i++;
	}
	return (1);
}

static int	check_philo_die(t_philo *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->data->nb_philo)
	{
		pthread_mutex_lock(&monitor->data->data_mutex);
		if (get_timestamp(monitor) - monitor[i].last_meal
			>= monitor->data->starve_time)
		{
			printf("%lu %d died\n", get_timestamp(monitor), monitor[i].id + 1);
			monitor->data->stop = 1;
			pthread_mutex_unlock(&monitor->data->data_mutex);
			return (1);
		}
		pthread_mutex_unlock(&monitor->data->data_mutex);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *data)
{
	t_philo	*monitor;

	monitor = (t_philo *)data;
	while (1)
	{
		if (check_philo_die(monitor) == 1)
			return (NULL);
		if (monitor->data->eat_nb != -1)
		{
			if (check_philo_eat(monitor))
			{
				pthread_mutex_lock(&monitor->data->data_mutex);
				monitor->data->stop = 1;
				pthread_mutex_unlock(&monitor->data->data_mutex);
				return (NULL);
			}
		}
		usleep(50);
	}
	return (NULL);
}
