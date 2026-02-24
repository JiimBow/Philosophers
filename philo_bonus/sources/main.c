/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:06:52 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 18:40:20 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	main(int ac, char **av)
{
	sem_t	sem;

	if (ac < 5 || ac > 6)
		return (error_message(0));
	if (!parser(av))
		return (error_message(1));
	
	return (0);
}
