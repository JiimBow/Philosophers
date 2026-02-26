/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:21:41 by jodone            #+#    #+#             */
/*   Updated: 2026/02/26 11:03:18 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	free_all(t_data *data, t_philo *philo, pid_t *pid)
{
	sem_close(data->sem_data);
	sem_close(data->fork);
	sem_unlink("sem_data");
	sem_unlink("sem_fork");
	free(pid);
	free(philo);
}
