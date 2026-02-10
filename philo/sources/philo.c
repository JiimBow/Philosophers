/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/09 21:44:54 by jimbow           ###   ########.fr       */
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

void	philo_init(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i;
		philo[i].nb_meals = 0;
		philo[i].last_meal = 0;
		philo[i].data = data;
		i++;
	}
}

void	destroy_mutex(t_data *data)
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

	philo = (t_philo *)data;
	f_left = philo->id;
	f_right = (philo->id + 1) % philo->data->nb_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex[f_left]);
		pthread_mutex_lock(&philo->data->mutex[f_right]);
		printf("%d is eating\n", philo->id + 1);
		usleep(philo->data->eat_time);
		philo->nb_meals++;
		pthread_mutex_unlock(&philo->data->mutex[f_left]);
		pthread_mutex_unlock(&philo->data->mutex[f_right]);
		usleep(philo->data->sleep_time);
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
	t_philo	philo;

	if (ac < 4 || ac > 5)
		return (1);
	data_init(&data, av);
	philo_init(&philo, &data);
	create_philo(&philo, &data);
}
