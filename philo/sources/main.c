/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/18 14:38:03 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*thread_routine(void *data)
{
	t_philo	*philo;
	int		f_left;
	int		f_right;

	philo = (t_philo *)data;
	f_left = philo->id;
	f_right = (philo->id + 1) % philo->data->nb_philo;
	while (philo->data->stop == 0 && philo->nb_meals != philo->data->eat_nb)
	{
		if (thinking_process(philo))
			break ;
		if (picking_fork(philo, f_left, f_right))
			break ;
		if (eating_process(philo, f_left, f_right))
			break ;
		pthread_mutex_unlock(&philo->data->fork[f_left]);
		pthread_mutex_unlock(&philo->data->fork[f_right]);
		if (sleeping_process(philo))
			break ;
	}
	philo->data->stop = 1;
	return (NULL);
}

void	*monitor_routine(void *data)
{
	t_philo	*monitor;
	int		i;

	monitor = (t_philo *)data;
	while (monitor->data->stop == 0)
	{
		i = 0;
		while (i < monitor->data->nb_philo)
		{
			pthread_mutex_lock(&monitor->data->stop_mutex);
			pthread_mutex_lock(&monitor->meal_mutex);
			if (get_timestamp(monitor) - monitor[i].last_meal >= monitor->data->starve_time)
			{
				pthread_mutex_unlock(&monitor->meal_mutex);
				printf("%lu %d died\n", get_timestamp(monitor), monitor->id + 1);
				monitor->data->stop = 1;
				pthread_mutex_unlock(&monitor->data->stop_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&monitor->meal_mutex);
			pthread_mutex_unlock(&monitor->data->stop_mutex);
			i++;
		}
	}
	return (NULL);
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
	pthread_join(monitor, NULL);
	mutex_destroy(philo);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	data.prog_time = 0;
	if (ac < 5 || ac > 6)
		return (1);
	if (!parser(av))
		return (1);
	data_init(&data, av);
	mutex_init(&data);
	philo = malloc(data.nb_philo * sizeof(t_philo));
	if (!philo)
		return (1);
	philo_init(philo, &data, get_time(philo));
	create_philo(philo, &data);
	return (0);
}
