/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:40:38 by jodone            #+#    #+#             */
/*   Updated: 2026/02/26 16:39:46 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	return (('0' <= c && c <= '9'));
}

int	arg_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] == '+')
		i++;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
