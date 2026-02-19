/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:26:50 by jodone            #+#    #+#             */
/*   Updated: 2026/02/19 20:15:09 by jimbow           ###   ########.fr       */
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

// static void	order_passage(t_data *data, t_philo *philo, int *first)
// {
// 	if (data->time_to_die < data->time_to_eat)
// 		return ;
// 	if (data->nb_philo % 2 == 0)
// 	{
// 		if (*first == 1 && (philo->id + 1) % 2 == 0)
// 			usleep(data->time_to_eat * THOUSAND);
// 		*first = 0;
// 	}
// 	if (data->nb_philo % 2 == 1)
// 	{
// 		if ((philo->id + 1) % 2 == 0)
// 			usleep(data->time_to_eat * THOUSAND);
// 		if (philo->id + 1 == data->nb_philo)
// 			usleep((data->time_to_eat + 1) * THOUSAND);
// 		if (*first == 0 && (philo->id + 1) % 2 == 1
// 			&& philo->id + 1 != data->nb_philo)
// 			usleep(data->time_to_eat * THOUSAND);
// 		*first = 0;
// 	}
// }

// void	*routine(void *arg)
// {
// 	t_philo	*philo;
// 	int		first;

// 	philo = (t_philo *)arg;
// 	first = 1;
// 	pthread_mutex_lock(&philo->data->mutex);
// 	philo->number_of_eating = philo->data->rotation;
// 	philo->start_rotation = get_time_in_ms();
// 	pthread_mutex_unlock(&philo->data->mutex);
// 	while (1)
// 	{
// 		if (is_thinking(philo->data, philo))
// 			break ;
// 		order_passage(philo->data, philo, &first);
// 		if (is_eating(philo->data, philo))
// 			break ;
// 		pthread_mutex_lock(&philo->data->mutex);
// 		philo->number_of_eating--;
// 		pthread_mutex_unlock(&philo->data->mutex);
// 		if (philo->number_of_eating == 0)
// 			break ;
// 		if (is_sleeping(philo->data, philo))
// 			break ;
// 	}
// 	return (NULL);
// }