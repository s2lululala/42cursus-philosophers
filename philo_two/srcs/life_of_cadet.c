/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_cadet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:54:45 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/13 00:54:47 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int				weekly_report(t_cadet *cadet, int content)
{
	sem_wait(cadet->right_to_report);
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
		printf(" %d is in thinking\n", cadet->number);
	else if (content == CONTENT_BLACKHOLE)
	{
		printf(" %d is died\n", cadet->number);
		return (1);
	}
	sem_post(cadet->right_to_report);
	return (0);
}

void			cadet_code_n_sleep(t_cadet *cadet)
{
	sem_wait(cadet->hand_on_keyboard);
	weekly_report(cadet, CONTENT_KEYBOARD);
	sem_wait(cadet->hand_on_keyboard);
	weekly_report(cadet, CONTENT_KEYBOARD);
	weekly_report(cadet, CONTENT_CODING);
	cadet->time_last_code = relative_time(0);
	spend_time(cadet->time_to_code);
	if (cadet->num_of_subject >= 0)
		cadet->num_of_subject++;
	sem_post(cadet->hand_on_keyboard);
	sem_post(cadet->hand_on_keyboard);
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

int				move_it_cadet(t_bocal *polabear)
{
	int			i;
	pthread_t	th_cadet[THREAD_MAX];

	i = 0;
	while (i < polabear->num_of_cadet)
	{
		pthread_create(&th_cadet[i], 0, life_of_cadet, &polabear->cadet[i]);
		pthread_detach(th_cadet[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < polabear->num_of_cadet)
	{
		pthread_create(&th_cadet[i], 0, life_of_cadet, &polabear->cadet[i]);
		pthread_detach(th_cadet[i]);
		i += 2;
	}
	return (0);
}
