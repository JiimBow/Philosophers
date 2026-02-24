/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 01:18:59 by jimbow            #+#    #+#             */
/*   Updated: 2026/02/24 17:55:16 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	data_init(t_data *data, char **av)
{
	data->stop = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->starve_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (av[5])
		data->eat_nb = ft_atoi(av[5]);
	else
		data->eat_nb = -1;
}

int	mutex_init(t_data *data)
{
	int	i;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			mutex_error_destroy(data, i, 0);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
	{
		mutex_error_destroy(data, i, 1);
		return (1);
	}
	return (0);
}

void	philo_init(t_philo *philo, t_data *data, size_t start_time)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i;
		philo[i].nb_meals = 0;
		philo[i].last_meal = 0;
		philo[i].data = data;
		philo[i].prog_time = start_time;
		i++;
	}
}
