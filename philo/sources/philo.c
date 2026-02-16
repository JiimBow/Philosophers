/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/16 16:33:28 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	data_init(t_data *data, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->starve_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (av[5])
		data->eat_nb = ft_atoi(av[5]);
}

int	mutex_init(t_data *data)
{
	int	i;

	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->mutex)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		i++;
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
	pthread_mutex_init(&philo->time_mutex, NULL);
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->mutex[i]);
		i++;
	}
	free(data->mutex);
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
		// while (1)
		// {
		// 	// if (pthread_mutex_lock(&philo->data->mutex[f_right]) == 0 && pthread_mutex_lock(&philo->data->mutex[f_left]) == 0)
		// 	// 	break ;
		// 	// else
		// 	// {
		// 	// 	pthread_mutex_unlock(&philo->data->mutex[f_left]);
		// 	// 	pthread_mutex_unlock(&philo->data->mutex[f_right]);
		// 	// }
		// 	usleep(10 * 1000);
		// 	printf("%lu %d coucou c'est moi\n", get_timestamp(philo), philo->id + 1);
		// 	if (get_timestamp(philo) - philo->last_meal >= philo->data->starve_time)
		// 	{
		// 		printf("%lu %d died\n", get_timestamp(philo), philo->id + 1);
		// 		break ;
		// 	}
		// }
		// pthread_mutex_lock(&philo->data->mutex[f_right]);
		// pthread_mutex_lock(&philo->data->mutex[f_left]);
		if (pthread_mutex_lock(&philo->data->mutex[f_right]) == 0)
			
		if (pthread_mutex_lock(&philo->data->mutex[f_left]) == 0)
		printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
		printf("%lu %d has taken a fork\n", get_timestamp(philo), philo->id + 1);
		printf("%lu %d is eating\n", get_timestamp(philo), philo->id + 1);
		philo->last_meal = get_timestamp(philo);
		usleep(philo->data->eat_time * 1000);
		philo->nb_meals++;
		pthread_mutex_unlock(&philo->data->mutex[f_left]);
		pthread_mutex_unlock(&philo->data->mutex[f_right]);
		printf("%lu %d is sleeping\n", get_timestamp(philo), philo->id + 1);
		usleep(philo->data->sleep_time * 1000);
	}
	return (NULL);
}

void	create_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, thread_routine, &philo[i]);
		i++;
	}
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
	data_init(&data, av);
	mutex_init(&data);
	philo = malloc(data.nb_philo * sizeof(t_philo));
	if (!philo)
		return (1);
	philo_init(philo, &data, get_time(philo));
	create_philo(philo, &data);
	mutex_destroy(&data);
}
