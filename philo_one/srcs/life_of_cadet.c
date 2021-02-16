/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_cadet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohyun <soohyun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:00:58 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/17 04:32:13 by soohyun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void			cadet_code_n_sleep(t_cadet *cadet)
{
	pthread_mutex_lock(cadet->hand_left);
	weekly_report(cadet, CONTENT_KEYBOARD);
	pthread_mutex_lock(cadet->hand_right);
	weekly_report(cadet, CONTENT_KEYBOARD);
	weekly_report(cadet, CONTENT_CODING);
	cadet->time_last_code = relative_time(0);
	spend_time(cadet->time_to_code);
	if (cadet->num_of_subject >= 0)
		cadet->num_of_subject++;
	pthread_mutex_unlock(cadet->hand_left);
	pthread_mutex_unlock(cadet->hand_right);
	weekly_report(cadet, CONTENT_SLEEP);
	spend_time(cadet->time_to_sleep);
	weekly_report(cadet, CONTENT_OASIS);
}

void			*life_of_cadet(void *data)
{
	t_cadet		*cadet;

	cadet = data;
	while (42)
		cadet_code_n_sleep(cadet);
}

int				move_it_cadet(t_bocal *polarbear)
{
	int			i;
	pthread_t	th_cadet[THREAD_MAX];

	i = 0;
	while (i < polarbear->num_of_cadet)
	{
		pthread_create(&th_cadet[i], 0, life_of_cadet, &polarbear->cadet[i]);
		pthread_detach(th_cadet[i]);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < polarbear->num_of_cadet)
	{
		pthread_create(&th_cadet[i], 0, life_of_cadet, &polarbear->cadet[i]);
		pthread_detach(th_cadet[i]);
		i += 2;
	}
	return (0);
}
