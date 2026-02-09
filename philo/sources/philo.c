/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/09 16:41:43 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	struct_init(t_mutex *philo, char **av)
{
	philo->starve_time = ft_atoi(av[2]);
	philo->eat_time = ft_atoi(av[3]);
	philo->sleep_time = ft_atoi(av[4]);
	if (av[5])
		philo->eat_nb = ft_atoi(av[5]);
}

void	*thread_routine(void *data)
{
	t_mutex	*philo;
	int		meals;

	philo = (t_mutex *)data;
	meals = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[philo->philo_id - 1]);
		pthread_mutex_lock(&philo->mutex[philo->philo_id % philo->nb_philo]);
		printf("philo %u : je prends une fourchette\n", philo->philo_id);
		printf("philo %u : je mange\n", philo->philo_id);
		usleep(philo->eat_time);
		meals++;
		pthread_mutex_unlock(&philo->mutex[philo->philo_id - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->philo_id % philo->nb_philo]);
		usleep(philo->sleep_time);
		if (meals == philo->eat_nb)
			break ;
	}
	return (NULL);
}

void	create_philo(t_mutex *philo, pthread_t tid)
{
	int			i;

	philo->eat_nb = -1;
	i = 0;
	pthread_create(&tid, NULL, thread_routine, philo);
}

int	main(int ac, char **av)
{
	int			i;
	int			nb_thread;
	t_mutex		*philo;
	pthread_t	*tids;

	if (ac < 4 || ac > 5)
		return (1);
	philo = malloc(sizeof(t_mutex) * ft_atoi(av[1]));
	philo->nb_philo = ft_atoi(av[1]);
	philo->mutex = malloc(philo->nb_philo * sizeof(pthread_mutex_t));
	tids = NULL;
	struct_init(philo, av);
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_init(&philo->mutex[i], NULL);
		i++;
	}
	nb_thread = 0;
	while (nb_thread < philo->nb_philo)
	{
		philo->philo_id = nb_thread + 1;
		create_philo(philo, tids[nb_thread]);
		nb_thread++;
	}
	nb_thread = 0;
	while (nb_thread < philo->nb_philo)
	{
		pthread_join(tids[nb_thread], NULL);
		nb_thread++;
	}
	while (i > 0)
	{
		pthread_mutex_destroy(&philo->mutex[i - 1]);
		i--;
	}
}
