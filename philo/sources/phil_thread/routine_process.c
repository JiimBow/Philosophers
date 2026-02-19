/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:26:50 by jodone            #+#    #+#             */
/*   Updated: 2026/02/19 11:33:43 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	thinking_process(t_philo *philo)
{
	printf("%lu %d is thinking\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (0);
}

int	eating_process(t_philo *philo, int f_left, int f_right)
{
	size_t	eating;

	printf("%lu %d is eating\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_timestamp(philo);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	eating = 0;
	while (eating <= philo->data->eat_time)
	{
		usleep(10 * 1000);
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			pthread_mutex_unlock(&philo->data->fork[f_left]);
			pthread_mutex_unlock(&philo->data->fork[f_right]);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		eating += 10;
	}
	return (0);
}

int	sleeping_process(t_philo *philo)
{
	printf("%lu %d is sleeping\n", get_timestamp(philo), philo->id + 1);
	usleep(philo->data->sleep_time * 1000);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (0);
}

int	picking_fork(t_philo *philo, int f_left, int f_right)
{
	usleep(philo->id * 10);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->data->fork[f_left]);
	else
		pthread_mutex_lock(&philo->data->fork[f_right]);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (philo->id % 2 != 0)
			pthread_mutex_unlock(&philo->data->fork[f_left]);
		else
			pthread_mutex_unlock(&philo->data->fork[f_right]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->data->fork[f_right]);
	else
		pthread_mutex_lock(&philo->data->fork[f_left]);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_unlock(&philo->data->fork[f_left]);
		pthread_mutex_unlock(&philo->data->fork[f_right]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
	return (0);
}
