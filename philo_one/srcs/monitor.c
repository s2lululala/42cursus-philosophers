/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohyun <soohyun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:01:05 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/17 04:22:32 by soohyun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int					weekly_report(t_cadet *cadet, int content)
{
	pthread_mutex_lock(cadet->right_to_report);
	if (content == CONTENT_SUCCESS)
	{
		printf("everybody have enough meal!\n");
		return (1);
	}
	printf("%lums", relative_time(cadet->time_start) / 1000);
	if (content == CONTENT_SUCCESS)
		return (CONTENT_SUCCESS);
	else if (content == CONTENT_KEYBOARD)
		printf(" %d has taken a fork\n", cadet->number);
	else if (content == CONTENT_CODING)
		printf(" %d is eating\n", cadet->number);
	else if (content == CONTENT_SLEEP)
		printf(" %d is sleeping\n", cadet->number);
	else if (content == CONTENT_OASIS)
		printf(" %d is thinking\n", cadet->number);
	else if (content == CONTENT_BLACKHOLE)
	{
		printf(" %d is died\n", cadet->number);
		return (1);
	}
	pthread_mutex_unlock(cadet->right_to_report);
	return (0);
}

void				*call_from_bocal(void *data)
{
	t_bocal			*polarbear;
	t_cadet			*cadet;
	int				i;

	polarbear = data;
	i = 0;
	while (42)
	{
		cadet = &polarbear->cadet[i];
		if (polarbear->time_to_blackhole < relative_time(cadet->time_last_code))
			if (weekly_report(cadet, CONTENT_BLACKHOLE))
				break ;
		if (cadet->num_of_subject >= 0 && \
		cadet->num_of_subject >= polarbear->min_of_subject)
		{
			polarbear->num_of_holly_work--;
			cadet->num_of_subject = -THREAD_MAX;
		}
		if (!polarbear->num_of_holly_work)
			if (weekly_report(cadet, CONTENT_SUCCESS))
				break ;
		i = i == polarbear->num_of_cadet - 1 ? 0 : i + 1;
		usleep(100);
	}
	return (0);
}

int					cadet_inspection(t_bocal *polarbear)
{
	if (pthread_create(&polarbear->th_bocal, 0, call_from_bocal, polarbear))
		return (-1);
	if (pthread_join(polarbear->th_bocal, 0))
		return (-1);
	else
		return (0);
}
