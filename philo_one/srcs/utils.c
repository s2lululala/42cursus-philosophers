/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:01:35 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/12 23:01:38 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

size_t				relative_time(size_t time_start)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000000 + current.tv_usec - time_start);
}

void				spend_time(size_t coding_time)
{
	size_t			start_time;

	start_time = relative_time(0);
	while (relative_time(0) < start_time + coding_time)
		;
}

int					ft_atoi(const char *str)
{
	long long		result;
	int				i;
	int				sign;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
