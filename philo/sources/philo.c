/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/02 16:09:04 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*thread_routine(void *data)
{
	t_mutex	*mutex;
	int		meals;

	mutex = (t_mutex *)data;
	meals = 0;
	while (1)
	{
		pthread_mutex_lock(&mutex->mutex[mutex->philo_id - 1]);
		printf("philo %u : je prends une fourchette\n", mutex->philo_id);
		printf("philo %u : je mange\n", mutex->philo_id);
		meals++;
		pthread_mutex_unlock(&mutex->mutex[mutex->philo_id - 1]);
		if (meals == mutex->eat_nb)
			break ;
	}
	return (NULL);
}

void	create_philo(int nb_philo)
{
	pthread_t	tid;
	t_mutex		mutex;
	int			i;

	mutex.philo_id = nb_philo;
	mutex.eat_nb = -1;
	mutex.mutex = malloc(nb_philo * sizeof(pthread_mutex_t));
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&mutex.mutex[i], NULL);
		i++;
	}
	pthread_create(&tid, NULL, thread_routine, &mutex);
	pthread_join(tid, NULL);
	while (i > 0)
	{
		pthread_mutex_destroy(&mutex.mutex[i - 1]);
		i--;
	}
}

int	main(int ac, char **av)
{
	int		nb_philo;

	if (ac < 4 || ac > 5)
		return (1);
	nb_philo = 1;
	while (nb_philo <= atoi(av[1]))
	{
		create_philo(nb_philo);
		nb_philo++;
	}
}
