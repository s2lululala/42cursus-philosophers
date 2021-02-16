/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:54:58 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/13 00:55:02 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int				ft_isvalidarg(int argc, char *argv[])
{
	int			i;

	i = 0;
	while (i < argc)
	{
		if (*argv[i] == 0)
			return (0);
		while (*argv[i] && *argv[i] >= '0' && *argv[i] <= '9')
			argv[i]++;
		if (*argv[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int				args_parse(int argc, char *argv[], t_bocal *polarbear)
{
	if (argc != 5 && argc != 6 && ft_isvalidarg(argc, argv) == 0)
		return (-1);
	sem_unlink("keyboards");
	sem_unlink("right_to_report");
	polarbear->num_of_cadet = ft_atoi(argv[1]);
	polarbear->time_to_blackhole = ft_atoi(argv[2]) * 1000;
	polarbear->time_to_code = ft_atoi(argv[3]) * 1000;
	polarbear->time_to_sleep = ft_atoi(argv[4]) * 1000;
	polarbear->time_start = relative_time(0);
	polarbear->min_of_subject = -1;
	polarbear->num_of_holly_work = polarbear->num_of_cadet;
	if (argc == 6)
		polarbear->min_of_subject = ft_atoi(argv[5]);
	if ((polarbear->keyboards = sem_open("keyboards", O_CREAT, \
	S_IRWXU, polarbear->num_of_cadet)) == SEM_FAILED)
		return (-1);
	if ((polarbear->right_to_report = sem_open("right_to_report",\
	O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (-1);
	return (0);
}

void			cadet_orientation(t_bocal *polarbear)
{
	int			i;

	i = 0;
	while (i < polarbear->num_of_cadet)
	{
		polarbear->cadet[i].number = i + 1;
		polarbear->cadet[i].num_of_subject = 0;
		if (polarbear->min_of_subject == -1)
			polarbear->cadet[i].num_of_subject = -1;
		polarbear->cadet[i].time_to_blackhole = polarbear->time_to_blackhole;
		polarbear->cadet[i].time_to_code = polarbear->time_to_code;
		polarbear->cadet[i].time_to_sleep = polarbear->time_to_sleep;
		polarbear->cadet[i].time_start = polarbear->time_start;
		polarbear->cadet[i].time_last_code = polarbear->time_start;
		polarbear->cadet[i].hand_on_keyboard = polarbear->keyboards;
		polarbear->cadet[i].right_to_report = polarbear->right_to_report;
		i++;
	}
}

int				main(int argc, char *argv[])
{
	int			i;
	t_bocal		polarbear;

	i = -1;
	if (args_parse(argc, argv, &polarbear) < 0)
	{
		sem_close(polarbear.keyboards);
		sem_unlink("keyboards");
		sem_close(polarbear.right_to_report);
		sem_unlink("right_to_report");
		return (-1);
	}
	cadet_orientation(&polarbear);
	move_it_cadet(&polarbear);
	return (cadet_inspection(&polarbear));
}
