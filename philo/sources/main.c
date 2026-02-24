/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 16:55:14 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

	if (ac < 5 || ac > 6)
		return (1);
	if (!parser(av))
		return (1);
	data_init(&data, av);
	if (mutex_init(&data) == 1)
		return (1);
	philo = malloc(data.nb_philo * sizeof(t_philo));
	if (!philo)
	{
		free(data.fork);
		return (1);
	}
	philo_init(philo, &data, get_time(philo));
	create_philo(philo, &data);
	return (0);
}
