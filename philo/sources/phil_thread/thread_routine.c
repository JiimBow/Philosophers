/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:54:23 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 17:27:09 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	multiple_philo(t_philo *philo, int f_left, int f_right)
{
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

void	*thread_routine(void *data)
{
	t_philo	*philo;
	int		f_left;
	int		f_right;

	philo = (t_philo *)data;
	if (philo->data->nb_philo == 1)
	{
		printf("%lu %d is thinking\n", get_timestamp(philo), philo->id + 1);
		printf("%lu %d has taken a fork\n",
			get_timestamp(philo), philo->id + 1);
	}
	else
	{
		f_left = philo->id;
		f_right = (philo->id + 1) % philo->data->nb_philo;
		multiple_philo(philo, f_left, f_right);
	}
	return (NULL);
}
