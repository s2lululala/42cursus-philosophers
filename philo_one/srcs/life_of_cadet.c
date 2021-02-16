/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_cadet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:00:58 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/17 02:30:39 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int				weekly_report(t_cadet *cadet, int content)
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

void			cadet_code_n_sleep_last(t_cadet *cadet)
{
	pthread_mutex_lock(cadet->hand_right);
	weekly_report(cadet, CONTENT_KEYBOARD);
	pthread_mutex_lock(cadet->hand_left);
	weekly_report(cadet, CONTENT_KEYBOARD);
	weekly_report(cadet, CONTENT_CODING);
	cadet->time_last_code = relative_time(0);
	spend_time(cadet->time_to_code);
	if (cadet->num_of_subject >= 0)
		cadet->num_of_subject++;
	pthread_mutex_unlock(cadet->hand_right);
	pthread_mutex_unlock(cadet->hand_left);
	weekly_report(cadet, CONTENT_SLEEP);
	spend_time(cadet->time_to_sleep);
	weekly_report(cadet, CONTENT_OASIS);
}

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
	while (i < polarbear->num_of_cadet - 1)
	{
		pthread_create(&th_cadet[i], 0, life_of_cadet, &polarbear->cadet[i]);
		pthread_detach(th_cadet[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < polarbear->num_of_cadet - 1)
	{
		pthread_create(&th_cadet[i], 0, life_of_cadet, &polarbear->cadet[i]);
		pthread_detach(th_cadet[i]);
		i += 2;
	}
	i = polarbear->num_of_cadet - 1;
	pthread_create(&th_cadet[i], 0, life_of_cadet, &polarbear->cadet[i]);
	pthread_detach(th_cadet[i]);
	return (0);
}
