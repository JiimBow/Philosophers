/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:44:39 by jodone            #+#    #+#             */
/*   Updated: 2026/02/26 15:04:43 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	*monitor_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	sem_wait(philo->data->monitor_check);
	sem_post(philo->data->philo_die);
	return (NULL);
}
