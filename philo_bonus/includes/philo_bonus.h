/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:07:07 by jodone            #+#    #+#             */
/*   Updated: 2026/02/25 18:35:42 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>

typedef struct s_data
{
	sem_t			*sem_data;
	sem_t			*fork;
	int				nb_philo;
	size_t			eat_time;
	size_t			starve_time;
	size_t			sleep_time;
	int				eat_nb;
	size_t			prog_time;
	struct timeval	tv;
	int				stop;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			nb_meals;
	size_t		last_meal;
	t_data		*data;
	// pthread_t	thread;
}	t_philo;

// INITIALISATION
void	data_init(t_data *data, char **av, size_t start_time);
void	philo_init(t_philo *philo, t_data *data);

// GET_TIME
size_t	get_time(t_data *data);
size_t	get_timestamp(t_data *data);
int		usleep_time(t_philo *philo, size_t limit);

// BASIC_FUNC
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		arg_is_digit(char *str);

// ROUTINE_PROCESS
void	philo_routine_start(t_philo *philo);
void	*thread_routine(void *data);
int		thinking_process(t_philo *philo);
int		picking_fork(t_philo *philo);
int		eating_process(t_philo *philo);
int		sleeping_process(t_philo *philo);

// ERROR_MANAGEMENT
int		error_message(int code);

// PARSING
int		parser(char **av);

#endif