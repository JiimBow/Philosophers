/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:26:50 by jodone            #+#    #+#             */
/*   Updated: 2026/02/19 16:19:50 by jodone           ###   ########.fr       */
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
	size_t	eating;

	pthread_mutex_lock(&philo->data->data_mutex);
	printf("%lu %d is eating\n", get_timestamp(philo), philo->id + 1);
	philo->last_meal = get_timestamp(philo);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	eating = 0;
	while (eating <= philo->data->eat_time)
	{
		usleep(10 * 1000);
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			pthread_mutex_unlock(&philo->data->fork[f_left]);
			pthread_mutex_unlock(&philo->data->fork[f_right]);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		eating += 10;
	}
	return (0);
}

int	sleeping_process(t_philo *philo)
{
	size_t	sleeping;

	pthread_mutex_lock(&philo->data->data_mutex);
	printf("%lu %d is sleeping\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->data->data_mutex);
	sleeping = 0;
	while (sleeping <= philo->data->sleep_time)
	{
		usleep(10 * 1000);
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		sleeping += 10;
	}
	return (0);
}

int	picking_fork(t_philo *philo, int f_left, int f_right)
{
	usleep(philo->id * 10);
	if (philo->id % 2 != 0 && philo->nb_meals == 0)
		usleep(philo->data->eat_time * 1000);
	else if (philo->id %2 == 0 && philo->id + 1 == philo->data->nb_philo && philo->nb_meals == 0)
		usleep(philo->data->eat_time * 2000);
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
