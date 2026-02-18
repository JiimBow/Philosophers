/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:26:50 by jodone            #+#    #+#             */
/*   Updated: 2026/02/18 18:52:22 by jodone           ###   ########.fr       */
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
	pthread_mutex_unlock(&philo->data->meal_mutex);
	philo->nb_meals++;
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
	while (1)
	{
		pthread_mutex_lock(&philo->data->order_mutex);
		if ((philo->data->order == 0 && philo->id % 2 == 0)
		|| (philo->data->order == 1 && philo->id % 2 != 0))
		{
			pthread_mutex_unlock(&philo->data->order_mutex);
			pthread_mutex_lock(&philo->data->fork[f_left]);
			break ;
		}
		pthread_mutex_unlock(&philo->data->order_mutex);
	}
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_unlock(&philo->data->fork[f_right]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_lock(&philo->data->fork[f_right]);
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
