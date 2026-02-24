/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:35:40 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 15:15:06 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	usleep_time(t_philo *philo, size_t limit)
{
	size_t	sleep_time;
	size_t	start_sleep;

	sleep_time = 0;
	while (sleep_time < limit)
	{
		start_sleep = get_time(philo);
		usleep(10);
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
