/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:36:17 by jodone            #+#    #+#             */
/*   Updated: 2026/02/19 11:06:21 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	mutex_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->fork[i]);
		pthread_mutex_unlock(&philo->data->fork[i]);
		pthread_mutex_destroy(&philo->data->fork[i]);
		i++;
	}
	free(philo->data->fork);
	pthread_mutex_destroy(&philo->data->meal_mutex);
	pthread_mutex_destroy(&philo->data->print_mutex);
	free(philo);
}
