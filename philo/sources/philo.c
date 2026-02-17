/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/17 01:55:41 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
}

void	*thread_routine(void *data)
{
	t_philo	*philo;
	int		f_left;
	int		f_right;
	size_t	time_of_death;
	size_t	timestamp;

	philo = (t_philo *)data;
	f_left = philo->id;
	f_right = (philo->id + 1) % philo->data->nb_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->time_mutex);
		timestamp = get_timestamp(philo);
		time_of_death = timestamp + philo->data->starve_time;
		printf("%lu %d is thinking\n", get_timestamp(philo), philo->id + 1);
		size_t timeofdeath = get_timestamp(philo) + philo->data->starve_time;
		printf("%lu %lu is time of death from %d\n", get_timestamp(philo), timeofdeath, philo->id + 1);
		pthread_mutex_unlock(&philo->time_mutex);
		// pthread_mutex_lock(&philo->data->fork[f_right]);
		// pthread_mutex_lock(&philo->data->fork[f_left]);
		printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
		printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
		printf("%lu %d is eating\n", get_timestamp(philo), philo->id + 1);
		philo->last_meal = get_timestamp(philo);
		usleep(philo->data->eat_time * 1000);
		philo->nb_meals++;
		pthread_mutex_unlock(&philo->data->fork[f_left]);
		pthread_mutex_unlock(&philo->data->fork[f_right]);
		printf("%lu %d is sleeping\n", get_timestamp(philo), philo->id + 1);
		usleep(philo->data->sleep_time * 1000);
	}
	return (NULL);
}

void	monitor_routine(void *data)
{
	t_data	*monitor;
	int		i;

	monitor = (t_philo *)data;
	while (monitor->stop == 0)
	{
		i = 0;
		while (i < monitor->nb_philo)
		{
			pthread_mutex_lock(&monitor->stop_mutex);
			if (get_timestamp(&monitor->philo) - monitor->philo[i].last_meal >= monitor->starve_time)
			{
				printf("%lu %d died\n", get_timestamp(monitor->philo), monitor->philo->id + 1);
				monitor->stop = 1;
				pthread_mutex_unlock(&monitor->stop_mutex);
				return ;
			}
			pthread_mutex_unlock(&monitor->stop_mutex);
			i++;
		}
	}
}

void	create_philo(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, thread_routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, philo);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	data.prog_time = 0;
	if (ac < 4 || ac > 5)
		return (1);
	data_init(philo, &data, av);
	mutex_init(&data);
	philo = malloc(data.nb_philo * sizeof(t_philo));
	if (!philo)
		return (1);
	philo_init(philo, &data, get_time(philo));
	create_philo(philo, &data);
	mutex_destroy(&data);
}
