/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/19 16:29:18 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*thread_routine(void *data)
{
	t_philo	*philo;
	int		f_left;
	int		f_right;

	philo = (t_philo *)data;
	if (philo->data->nb_philo == 1)
	{
		printf("%lu %d is thinking\n", get_timestamp(philo), philo->id + 1);
		printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
	}
	else
	{
		f_left = philo->id;
		f_right = (philo->id + 1) % philo->data->nb_philo;
		while (philo->nb_meals != philo->data->eat_nb)
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
