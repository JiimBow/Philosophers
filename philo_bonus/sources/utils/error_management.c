/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:17:48 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 18:28:36 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	error_message(int code)
{
	if (code == 0)
		printf("Program must have 4 or 5 arguments\n");
	else if (code == 1)
		printf("Program must have numeric arguments\n");
	return (1);
}
