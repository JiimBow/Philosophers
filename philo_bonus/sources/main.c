/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:06:52 by jodone            #+#    #+#             */
/*   Updated: 2026/03/02 17:06:55 by jodone           ###   ########.fr       */
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

void	child_process(t_data *data, t_philo *philo, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			free_child(data, philo, pid);
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)
		{
			create_thread(&philo[i]);
			free_child(data, philo, pid);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	create_philo(t_data *data, t_philo *philo)
{
	int			i;
	int			status;
	pid_t		*pid;
	pthread_t	eat_check;

	pid = malloc(data->nb_philo * sizeof(pid_t));
	if (!pid)
	{
		close_all(data);
		free(philo);
		exit(EXIT_FAILURE);
	}
	child_process(data, philo, pid);
	pthread_create(&eat_check, NULL, eat_check_routine, data);
	sem_wait(philo->data->monitor_check);
	sem_post(philo->data->philo_die);
	pthread_join(eat_check, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free_all(data, philo, pid);
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
	sem_unlink("sem_all_eat");
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
