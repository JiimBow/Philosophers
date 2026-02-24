/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:35:40 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 16:38:53 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_routine_start(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 != 0 && philo->nb_meals == 0)
			usleep_time(philo, philo->data->eat_time / 2);
	}
	else
	{
		if (philo->id % 2 != 0)
			usleep_time(philo, philo->data->eat_time / 2);
		if (philo->id % 2 == 0 && philo->id + 1 == philo->data->nb_philo)
			usleep_time(philo, philo->data->eat_time / 2 + 1);
		else if (philo->id % 2 == 0 && philo->nb_meals != 0)
			usleep_time(philo, philo->data->eat_time / 2);
	}
}

int	usleep_time(t_philo *philo, size_t limit)
{
	size_t	sleep_time;
	size_t	start_sleep;

	sleep_time = 0;
	while (sleep_time < limit)
	{
		start_sleep = get_time(philo);
		usleep(500);
		sleep_time += get_time(philo) - start_sleep;
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	return (1);
}
