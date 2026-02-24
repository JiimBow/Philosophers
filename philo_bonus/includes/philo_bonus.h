/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:07:07 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 18:41:00 by jodone           ###   ########.fr       */
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



// BASIC_FUNC
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		arg_is_digit(char *str);

// ERROR_MANAGEMENT
int		error_message(int code);

// PARSING
int		parser(char **av);

#endif