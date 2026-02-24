/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:03:36 by jodone            #+#    #+#             */
/*   Updated: 2026/02/24 18:14:50 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	parser(char **av)
{
	int	i;

	if (ft_atoi(av[1]) <= 0)
		return (0);
	i = 1;
	while (av && av[i])
	{
		if (!av[i][0])
			return (0);
		if (!arg_is_digit(av[i]) || ft_atol(av[i]) > 2147483647
			|| ft_atol(av[i]) < -2147483648)
			return (0);
		i++;
	}
	return (1);
}
