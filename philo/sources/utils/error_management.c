/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:30:30 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 18:34:11 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	error_message(int code)
{
	if (code == 0)
		printf("Program must have 4 or 5 arguments\n");
	else if (code == 1)
		printf("Program must have numeric arguments\n");
	else if (code == 2)
		printf("Mutex init failed\n");
	else if (code == 3)
		printf("Malloc failed\n");
	else if (code == 4)
		printf("Pthread_create failed\n");
	return (1);
}
