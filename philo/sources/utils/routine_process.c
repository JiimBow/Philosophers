/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:26:50 by jodone            #+#    #+#             */
/*   Updated: 2026/02/17 17:38:52 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	thinking_process(t_philo *philo)
{
	printf("%lu %d is thinking\n", get_timestamp(philo), philo->id + 1);
	if (philo->data->stop == 1)
		return (1);
	return (0);
}

int	eating_process(t_philo *philo, int f_left, int f_right)
{
	size_t	eating;

	printf("%lu %d is eating\n", get_timestamp(philo), philo->id + 1);
	philo->nb_meals++;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_timestamp(philo);
	pthread_mutex_unlock(&philo->meal_mutex);
	eating = 0;
	while (eating <= philo->data->eat_time)
	{
		usleep(10 * 1000);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->fork[f_left]);
			pthread_mutex_unlock(&philo->data->fork[f_right]);
			return (1);
		}
		eating += 10;
	}
	return (0);
}

int	sleeping_process(t_philo *philo)
{
	printf("%lu %d is sleeping\n", get_timestamp(philo), philo->id + 1);
	usleep(philo->data->sleep_time * 1000);
	if (philo->data->stop == 1)
		return (1);
	return (0);
}

int	picking_fork(t_philo *philo, int f_left, int f_right)
{
	pthread_mutex_lock(&philo->data->fork[f_right]);
	printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_lock(&philo->data->fork[f_left]);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->fork[f_left]);
		pthread_mutex_unlock(&philo->data->fork[f_right]);
		return (1);
	}
	printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
	return (0);
}
