/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:18:47 by jodone            #+#    #+#             */
/*   Updated: 2026/02/19 16:26:36 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

size_t	get_time(t_philo *philo)
{
	size_t	result;

	gettimeofday(&philo->tv, NULL);
	result = (philo->tv.tv_sec * 1000) + (philo->tv.tv_usec / 1000);
	return (result);
}

size_t	get_timestamp(t_philo *philo)
{
	size_t	current_time;
	size_t	result;

	gettimeofday(&philo->tv, NULL);
	current_time = (philo->tv.tv_sec * 1000) + (philo->tv.tv_usec / 1000);
	result = current_time - philo->prog_time;
	return (result);
}
