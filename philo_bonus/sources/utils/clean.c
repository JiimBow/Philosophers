/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:21:41 by jodone            #+#    #+#             */
/*   Updated: 2026/03/02 15:41:33 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	close_all(t_data *data)
{
	sem_close(data->sem_data);
	sem_close(data->fork);
	sem_close(data->first_death);
	sem_close(data->philo_die);
	sem_close(data->monitor_check);
	sem_close(data->all_eat);
}

void	free_sem(t_data *data)
{
	close_all(data);
	sem_unlink("sem_data");
	sem_unlink("sem_fork");
	sem_unlink("sem_die");
	sem_unlink("sem_monitor");
	sem_unlink("sem_first_death");
	sem_unlink("sem_all_eat");
}

void	free_child(t_data *data, t_philo *philo, pid_t *pid)
{
	close_all(data);
	free(pid);
	free(philo);
}

void	free_all(t_data *data, t_philo *philo, pid_t *pid)
{
	free_sem(data);
	free(pid);
	free(philo);
}
