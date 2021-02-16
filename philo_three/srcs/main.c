/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:57:11 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/13 00:57:12 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int					ft_isvalidarg(int argc, char *argv[])
{
	int				i;

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

int					init_check_success(t_bocal *polarbear)
{
	int				i;
	char			*cadet_num;

	i = -1;
	while (++i < polarbear->num_of_cadet)
	{
		cadet_num = ft_itoa(i + 1);
		sem_unlink(cadet_num);
		polarbear->check_success[i] = sem_open(cadet_num, O_CREAT, S_IRWXU, 1);
		free(cadet_num);
	}
	return (0);
}

int					args_parse(int argc, char *argv[], t_bocal *polarbear)
{
	if (argc != 5 && argc != 6 && ft_isvalidarg(argc, argv) == 0)
		return (-1);
	sem_unlink("keyboards");
	sem_unlink("right_to_report");
	polarbear->num_of_cadet = ft_atoi(argv[1]);
	polarbear->cadet.time_to_blackhole = ft_atoi(argv[2]) * 1000;
	polarbear->cadet.time_to_code = ft_atoi(argv[3]) * 1000;
	polarbear->cadet.time_to_sleep = ft_atoi(argv[4]) * 1000;
	polarbear->cadet.time_start = relative_time(0);
	polarbear->cadet.time_last_code = polarbear->cadet.time_start;
	polarbear->cadet.min_of_subject = -1;
	if (argc == 6)
		polarbear->cadet.min_of_subject = ft_atoi(argv[5]);
	polarbear->cadet.num_of_subject = 0;
	if (polarbear->cadet.min_of_subject == -1)
		polarbear->cadet.num_of_subject = -1;
	if ((polarbear->keyboards = sem_open("keyboards", O_CREAT, \
	S_IRWXU, polarbear->num_of_cadet)) == SEM_FAILED)
		return (-1);
	if ((polarbear->right_to_report = sem_open("right_to_report",\
	O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (-1);
	polarbear->cadet.hand_on_keyboard = polarbear->keyboards;
	polarbear->cadet.right_to_report = polarbear->right_to_report;
	return (init_check_success(polarbear));
}

int					main(int argc, char *argv[])
{
	int				i;
	t_bocal			polarbear;

	i = -1;
	polarbear.absorbed = 0;
	if (args_parse(argc, argv, &polarbear) < 0)
	{
		sem_close(polarbear.keyboards);
		sem_unlink("keyboards");
		sem_close(polarbear.right_to_report);
		sem_unlink("right_to_report");
		return (-1);
	}
	move_it_cadet(&polarbear);
	return (cadet_inspection(&polarbear));
}
