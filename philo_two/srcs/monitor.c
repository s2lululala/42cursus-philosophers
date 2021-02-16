/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:55:06 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/13 00:55:08 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

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
