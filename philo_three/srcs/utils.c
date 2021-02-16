/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:57:25 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/13 00:57:26 by soohchoi         ###   ########.fr       */
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

char				*ft_itoa(int n)
{
	int				size;
	int				temp;
	char			*ret;

	size = 1;
	temp = n;
	while (temp > 9)
	{
		size++;
		temp /= 10;
	}
	if (!(ret = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ret[size--] = '\0';
	while (size + 1 > 0 && n >= 0)
	{
		ret[size--] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}
