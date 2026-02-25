/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:47:20 by jodone            #+#    #+#             */
/*   Updated: 2026/02/25 17:36:41 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	thinking_process(t_philo *philo)
{
	sem_wait(philo->data->sem_data);
	printf("%lu %d is thinking\n", get_timestamp(philo->data), philo->id + 1);
	if (philo->data->stop == 1)
	{
		sem_post(philo->data->sem_data);
		return (1);
	}
	sem_post(philo->data->sem_data);
	return (0);
}

int	picking_fork(t_philo *philo)
{
	philo_routine_start(philo);
	sem_wait(philo->data->fork);
	printf("%lu %d has taken a fork\n",
		get_timestamp(philo->data), philo->id + 1);
	sem_wait(philo->data->sem_data);
	if (philo->data->stop == 1)
	{
		sem_post(philo->data->fork);
		sem_post(philo->data->sem_data);
		return (1);
	}
	sem_post(philo->data->sem_data);
	sem_wait(philo->data->fork);
	printf("%lu %d has taken a fork\n",
		get_timestamp(philo->data), philo->id + 1);
	sem_wait(philo->data->sem_data);
	if (philo->data->stop == 1)
	{
		sem_post(philo->data->fork);
		sem_post(philo->data->fork);
		sem_post(philo->data->sem_data);
		return (1);
	}
	sem_post(philo->data->sem_data);
	return (0);
}

int	eating_process(t_philo *philo)
{
	sem_wait(philo->data->sem_data);
	if (philo->data->stop == 1)
	{
		sem_post(philo->data->sem_data);
		return (1);
	}
	printf("%lu %d is eating\n", get_timestamp(philo->data), philo->id + 1);
	philo->last_meal = get_timestamp(philo->data);
	philo->nb_meals++;
	sem_post(philo->data->sem_data);
	if (!usleep_time(philo, philo->data->eat_time))
	{
		sem_post(philo->data->fork);
		sem_post(philo->data->fork);
		return (1);
	}
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	return (0);
}

int	sleeping_process(t_philo *philo)
{
	sem_wait(philo->data->sem_data);
	if (philo->data->stop == 1)
	{
		sem_post(philo->data->sem_data);
		return (1);
	}
	printf("%lu %d is sleeping\n", get_timestamp(philo->data), philo->id + 1);
	sem_post(philo->data->sem_data);
	if (!usleep_time(philo, philo->data->sleep_time))
		return (1);
	return (0);
}
