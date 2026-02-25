/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:35:01 by jodone            #+#    #+#             */
/*   Updated: 2026/02/25 11:36:03 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

size_t	get_time(t_data *data)
{
	size_t	result;

	gettimeofday(&data->tv, NULL);
	result = (data->tv.tv_sec * 1000) + (data->tv.tv_usec / 1000);
	return (result);
}

size_t	get_timestamp(t_data *data)
{
	size_t	current_time;
	size_t	result;

	gettimeofday(&data->tv, NULL);
	current_time = (data->tv.tv_sec * 1000) + (data->tv.tv_usec / 1000);
	result = current_time - data->prog_time;
	return (result);
}
