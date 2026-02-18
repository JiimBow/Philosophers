/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:29:25 by jodone            #+#    #+#             */
/*   Updated: 2026/02/18 10:30:06 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	ft_atol(const char *nptr)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	i = 0;
	if (!nptr || !*nptr)
		return (0);
	while (nptr && (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = result * 10 + (nptr[i] - 48);
		if ((nptr[i + 1] < '0' || nptr[i + 1] > '9'))
			return (result * sign);
		i++;
	}
	return (result);
}
