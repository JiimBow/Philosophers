/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:58:21 by jodone            #+#    #+#             */
/*   Updated: 2026/02/09 16:00:10 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct	s_mutex
{
	pthread_mutex_t	*mutex;
	int				philo_id;
	int				nb_philo;
	int				eat_nb;
	int				eat_time;
	int				starve_time;
	int				sleep_time;
}	t_mutex;

int	ft_atoi(const char *nptr);

#endif