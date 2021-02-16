/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fortytwo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:57:00 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/13 00:57:02 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTYTWO_H
# define FORTYTWO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# define PROCESS_MAX 200
# define CONTENT_KEYBOARD 1
# define CONTENT_CODING 2
# define CONTENT_SLEEP 3
# define CONTENT_BLACKHOLE 4
# define CONTENT_SUCCESS 5
# define CONTENT_OASIS 6

typedef struct		s_cadet
{
	int				number;
	sem_t			*hand_on_keyboard;
	sem_t			*right_to_report;
	int				num_of_subject;
	size_t			time_start;
	size_t			time_to_blackhole;
	size_t			time_to_code;
	size_t			time_to_sleep;
	size_t			time_last_code;
	sem_t			*check_success;
	int				min_of_subject;
}					t_cadet;

typedef struct		s_bocal
{
	sem_t			*keyboards;
	sem_t			*right_to_report;
	int				absorbed;
	t_cadet			cadet;
	int				num_of_cadet;
	pthread_t		th_bocal;
	int				state[PROCESS_MAX];
	sem_t			*check_success[PROCESS_MAX];
	pid_t			pid_cadet[PROCESS_MAX];
}					t_bocal;

/*
**					life_of_cadet.c
*/
int					weekly_report(t_cadet *cadet, int content);
int					move_it_cadet(t_bocal *polabear);

/*
**					utils.c
*/
size_t				relative_time(size_t time_start);
void				spend_time(size_t coding_time);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);

/*
**					monitor.c
*/
void				*call_from_cadet(void *data);
int					cadet_inspection(t_bocal *polarbear);
int					free_resource(t_bocal *polarbear);

#endif
