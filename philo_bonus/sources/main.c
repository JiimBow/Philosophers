/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:06:52 by jodone            #+#    #+#             */
/*   Updated: 2026/02/26 11:08:43 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	create_thread(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, thread_routine, philo);
	pthread_join(thread, NULL);
}

void	create_philo(t_data *data, t_philo *philo)
{
	int		i;
	int		status;
	pid_t	*pid;

	i = 0;
	pid = malloc(data->nb_philo * sizeof(pid_t));
	while (i < data->nb_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit(EXIT_FAILURE);
		if (pid[i] == 0)
		{
			create_thread(&philo[i]);
			free_all(data, philo, pid);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (error_message(0));
	if (!parser(av))
		return (error_message(1));
	sem_unlink("sem_data");
	sem_unlink("sem_fork");
	data_init(&data, av, get_time(&data));
	philo = malloc(data.nb_philo * sizeof(t_philo));
	if (!philo)
	{
		free(philo);
		return (error_message(2));
	}
	philo_init(philo, &data);
	create_philo(&data, philo);
	return (0);
}
