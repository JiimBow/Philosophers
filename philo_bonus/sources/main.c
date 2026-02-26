/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:06:52 by jodone            #+#    #+#             */
/*   Updated: 2026/02/26 16:48:59 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	create_thread(t_philo *philo)
{
	pthread_t	thread;
	pthread_t	die_checker;

	pthread_create(&thread, NULL, thread_routine, philo);
	pthread_create(&die_checker, NULL, die_checker_routine, philo);
	checker_routine(philo);
	pthread_join(thread, NULL);
	pthread_join(die_checker, NULL);
}

void	create_philo(t_data *data, t_philo *philo)
{
	int		i;
	int		status;
	pid_t	*pid;

	i = 0;
	pid = malloc(data->nb_philo + 1 * sizeof(pid_t));
	if (!pid)
	{
		;
	}
	while (i < data->nb_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			free_all(data, philo, pid);
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)
		{
			create_thread(&philo[i]);
			free_all(data, philo, pid);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	sem_wait(philo->data->monitor_check);
	sem_post(philo->data->philo_die);
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
	sem_unlink("sem_die");
	sem_unlink("sem_monitor");
	sem_unlink("sem_first_death");
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
