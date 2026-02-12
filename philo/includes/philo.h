/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:21 by jodone            #+#    #+#             */
/*   Updated: 2026/02/12 17:26:29 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_data
{
	pthread_mutex_t	*mutex;
	int				nb_philo;
	int				eat_time;
	int				starve_time;
	int				sleep_time;
	int				eat_nb;
	unsigned long	prog_time;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			nb_meals;
	int			last_meal;
	pthread_t	thread;
	t_data		*data;
}	t_philo;


int	ft_atoi(const char *nptr);

#endif