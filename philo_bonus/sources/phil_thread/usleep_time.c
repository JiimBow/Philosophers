/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:22:40 by jodone            #+#    #+#             */
/*   Updated: 2026/03/03 13:17:10 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	philo_routine_start(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 != 0 && philo->nb_meals == 0)
			usleep_time(philo, philo->data->eat_time / 2);
	}
	else if (philo->data->nb_philo % 2 != 0
		&& philo->data->eat_time >= philo->data->sleep_time)
	{
		if (philo->id % 2 != 0)
			usleep_time(philo, philo->data->eat_time / 2);
		if (philo->id % 2 == 0 && philo->id + 1 == philo->data->nb_philo)
			usleep_time(philo, philo->data->eat_time / 2 + 1);
		else if (philo->id % 2 == 0 && philo->nb_meals != 0)
			usleep_time(philo, philo->data->eat_time / 2);
	}
	else if (philo->data->nb_philo % 2 != 0
		&& philo->data->eat_time < philo->data->sleep_time)
	{
		if (philo->id % 2 != 0 && philo->nb_meals == 0)
			usleep_time(philo, philo->data->eat_time / 2);
		if (philo->id % 2 == 0 && philo->id + 1 == philo->data->nb_philo
			&& philo->nb_meals == 0)
			usleep_time(philo, philo->data->eat_time / 2 + 1);
	}
}

int	usleep_time(t_philo *philo, size_t limit)
{
	size_t	sleep_time;
	size_t	start_sleep;

	sleep_time = 0;
	while (sleep_time < limit)
	{
		start_sleep = get_time(philo->data);
		usleep(500);
		sleep_time += get_time(philo->data) - start_sleep;
		sem_wait(philo->data->sem_data);
		if (philo->data->stop == 1)
		{
			sem_post(philo->data->sem_data);
			return (0);
		}
		sem_post(philo->data->sem_data);
	}
	return (1);
}
