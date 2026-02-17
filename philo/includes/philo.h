/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:21 by jodone            #+#    #+#             */
/*   Updated: 2026/02/17 15:25:14 by jodone           ###   ########.fr       */
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
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	int				nb_philo;
	int				stop;
	size_t			eat_time;
	size_t			starve_time;
	size_t			sleep_time;
	int				eat_nb;
	size_t			prog_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	size_t			last_meal;
	size_t			prog_time;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_data			*data;
	struct timeval	tv;
}	t_philo;

// UTILS
int		ft_atoi(const char *nptr);
size_t	get_time(t_philo *philo);
size_t	get_timestamp(t_philo *philo);

// INITIALISATION
void	data_init(t_data *data, char **av);
int		mutex_init(t_data *data);
void	philo_init(t_philo *philo, t_data *data, size_t start_time);

// MEMORY_MANAGEMENT
void	mutex_destroy(t_philo *philo);
void	kill_thread(t_philo *philo);

#endif