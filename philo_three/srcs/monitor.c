/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohyun <soohyun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:57:19 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/17 12:03:55 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void			*call_from_cadet(void *data)
{
	t_cadet		*cadet;

	cadet = data;
	while (42)
	{
		if (cadet->time_to_blackhole < relative_time(cadet->time_last_code))
		{
			weekly_report(cadet, CONTENT_BLACKHOLE);
			exit(CONTENT_BLACKHOLE);
		}
		if (cadet->num_of_subject >= 0 && \
		cadet->num_of_subject >= cadet->min_of_subject)
		{
			sem_post(cadet->check_success);
			cadet->num_of_subject = -1;
		}
		usleep(100);
	}
	return (0);
}

void			*send_jiwongeum(void *data)
{
	int			i;
	t_bocal		*polarbear;

	i = -1;
	polarbear = data;
	while (++i < polarbear->num_of_cadet)
		sem_wait(polarbear->check_success[i]);
	if (polarbear->absorbed)
		return (0);
	weekly_report(&polarbear->cadet, CONTENT_SUCCESS);
	i = -1;
	while (++i < polarbear->num_of_cadet)
		kill(polarbear->pid_cadet[i], SIGKILL);
	free_resource(polarbear);
	exit(0);
	return (0);
}

int				free_resource(t_bocal *polarbear)
{
	int			i;
	char		*cadet_num;

	i = -1;
	if (polarbear->cadet.right_to_report)
	{
		sem_close(polarbear->cadet.right_to_report);
		sem_unlink("right_to_report");
	}
	if (polarbear->cadet.hand_on_keyboard)
	{
		sem_close(polarbear->cadet.hand_on_keyboard);
		sem_unlink("keyboards");
	}
	if (*polarbear->check_success)
		while (++i < polarbear->num_of_cadet)
		{
			cadet_num = ft_itoa(i + 1);
			sem_post(polarbear->check_success[i]);
			sem_close(polarbear->check_success[i]);
			sem_unlink(cadet_num);
			free(cadet_num);
		}
	return (0);
}

int				cadet_inspection(t_bocal *polarbear)
{
	int			i;
	pthread_t	jiwongeum;

	i = 0;
	usleep(200);
	pthread_create(&jiwongeum, 0, send_jiwongeum, polarbear);
	pthread_detach(jiwongeum);
	while (42)
	{
		if (waitpid(polarbear->pid_cadet[i], &polarbear->state[i], \
		WNOHANG | WCONTINUED | WUNTRACED))
		{
			if (WEXITSTATUS(polarbear->state[i]) == CONTENT_BLACKHOLE)
			{
				polarbear->absorbed = 1;
				i = -1;
				while (++i < polarbear->num_of_cadet)
					kill(polarbear->pid_cadet[i], SIGKILL);
				free_resource(polarbear);
				return (0);
			}
		}
		i = i == polarbear->num_of_cadet - 1 ? 0 : i + 1;
	}
	return (0);
}
