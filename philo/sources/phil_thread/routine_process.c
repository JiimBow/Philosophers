/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:26:50 by jodone            #+#    #+#             */
/*   Updated: 2026/02/19 17:45:32 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	thinking_process(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	printf("%lu %d is thinking\n", get_timestamp(philo), philo->id + 1);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (0);
}

int	eating_process(t_philo *philo, int f_left, int f_right)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	printf("%lu %d is eating\n", get_timestamp(philo), philo->id + 1);
	philo->last_meal = get_timestamp(philo);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (!usleep_time(philo, philo->data->eat_time))
	{
		pthread_mutex_unlock(&philo->data->fork[f_left]);
		pthread_mutex_unlock(&philo->data->fork[f_right]);
		return (1);
	}
	return (0);
}

int	sleeping_process(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	printf("%lu %d is sleeping\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (!usleep_time(philo, philo->data->sleep_time))
		return (1);
	return (0);
}

int	picking_fork(t_philo *philo, int f_left, int f_right)
{
	usleep(philo->id * 100);
	if (philo->id % 2 != 0 && philo->nb_meals == 0)
		usleep_time(philo, philo->data->eat_time);
	// if (philo->id % 2 == 0 && philo->id + 1 == philo->data->nb_philo && philo->nb_meals == 0)
	// 	usleep_time(philo, philo->data->eat_time * 2);
	// if (philo->id % 2 == 0 && philo->nb_meals % 2 != 0)
	// 	usleep_time(philo, philo->data->eat_time);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->data->fork[f_left]);
	else
		pthread_mutex_lock(&philo->data->fork[f_right]);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(&philo->data->fork[f_left]);
		else
			pthread_mutex_unlock(&philo->data->fork[f_right]);
		return (1);
	}
	printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->data->fork[f_right]);
	else
		pthread_mutex_lock(&philo->data->fork[f_left]);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_unlock(&philo->data->fork[f_left]);
		pthread_mutex_unlock(&philo->data->fork[f_right]);
		return (1);
	}
	printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (0);
}