/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fortytwo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohchoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 00:54:13 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/13 00:54:15 by soohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTYTWO_H
# define FORTYTWO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/time.h>
# define THREAD_MAX 200
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
}					t_cadet;

typedef struct		s_bocal
{
	sem_t			*keyboards;
	sem_t			*right_to_report;
	t_cadet			cadet[THREAD_MAX];
	int				num_of_cadet;
	int				num_of_holly_work;
	size_t			time_start;
	size_t			time_to_blackhole;
	size_t			time_to_code;
	size_t			time_to_sleep;
	int				min_of_subject;
	pthread_t		th_bocal;
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

/*
**					monitor.c
*/
int					cadet_inspection(t_bocal *polarbear);

#endif
