/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:36:17 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 18:00:44 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	mutex_error_destroy(t_data *data, int i, int d_mutex)
{
	if (d_mutex == 1)
		pthread_mutex_destroy(&data->data_mutex);
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i--;
	}
	free(data->fork);
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->fork[i]);
		pthread_mutex_unlock(&data->fork[i]);
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	pthread_mutex_destroy(&data->data_mutex);
}
