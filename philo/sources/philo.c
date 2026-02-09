/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:13 by jodone            #+#    #+#             */
/*   Updated: 2026/02/09 17:08:50 by jodone           ###   ########.fr       */
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
		pthread_mutex_lock(&philo[philo->philo_id - 1].mutex);
		pthread_mutex_lock(&philo[philo->philo_id % philo->nb_philo].mutex);
		printf("philo %u : je prends une fourchette\n", philo->philo_id);
		printf("philo %u : je mange\n", philo->philo_id);
		usleep(philo->eat_time);
		meals++;
		pthread_mutex_unlock(&philo[philo->philo_id - 1].mutex);
		pthread_mutex_unlock(&philo[philo->philo_id % philo->nb_philo].mutex);
		usleep(philo->sleep_time);
		if (meals == philo->eat_nb)
			break ;
	}
	return (NULL);
}

void	create_philo(t_mutex *philo, pthread_t *tid)
{
	int			i;

	philo->eat_nb = -1;
	i = 0;
	pthread_create(tid, NULL, thread_routine, philo);
}

int	main(int ac, char **av)
{
	int			i;
	int			nb_mutex;
	t_mutex		*philo;
	pthread_t	*tid;

	if (ac < 4 || ac > 5)
		return (1);
	philo = malloc(sizeof(t_mutex) * ft_atoi(av[1]));
	if (!philo)
		return (1);
	philo->nb_philo = ft_atoi(av[1]);
	tid = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!tid)
		return (1);
	nb_mutex = 0;
	while (nb_mutex < philo->nb_philo)
	{
		pthread_mutex_init(&philo[nb_mutex].mutex, NULL);
		nb_mutex++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		philo[i].philo_id = i + 1;
		struct_init(&philo[i], av);
		create_philo(&philo[i], &tid[i]);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	while (nb_mutex > 0)
	{
		pthread_mutex_destroy(&philo[nb_mutex - 1].mutex);
		nb_mutex--;
	}
}
