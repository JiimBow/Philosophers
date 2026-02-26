/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:52:31 by jodone            #+#    #+#             */
/*   Updated: 2026/02/26 14:33:44 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	data_init(t_data *data, char **av, size_t start_time)
{
	data->nb_philo = ft_atoi(av[1]);
	data->starve_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (av[5])
		data->eat_nb = ft_atoi(av[5]);
	else
		data->eat_nb = -1;
	data->prog_time = start_time;
	data->sem_data = sem_open("sem_data", O_CREAT, 0664, 1);
	data->fork = sem_open("sem_fork", O_CREAT, 0664, data->nb_philo);
	data->philo_die = sem_open("sem_die", O_CREAT, 0664, 0);
	data->monitor_check = sem_open("sem_monitor", O_CREAT, 0664, 0);
	data->stop = 0;
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
