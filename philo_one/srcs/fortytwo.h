/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fortytwo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohyun <soohyun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:00:47 by soohchoi          #+#    #+#             */
/*   Updated: 2021/02/17 02:34:50 by soohyun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTYTWO_H
# define FORTYTWO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
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
	pthread_mutex_t	*hand_right;
	pthread_mutex_t	*hand_left;
	pthread_mutex_t	*right_to_report;
	int				num_of_subject;
	size_t			time_start;
	size_t			time_to_blackhole;
	size_t			time_to_code;
	size_t			time_to_sleep;
	size_t			time_last_code;
}					t_cadet;

typedef struct		s_bocal
{
	pthread_mutex_t	keyboards[THREAD_MAX];
	pthread_mutex_t	right_to_report;
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
void				cadet_code_n_sleep_last(t_cadet *cadet);
void				cadet_code_n_sleep(t_cadet *cadet);
void				*life_of_cadet_last(void *data);
void				*life_of_cadet(void *data);
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
int					weekly_report(t_cadet *cadet, int content);
void				*call_from_bocal(void *data);
int					cadet_inspection(t_bocal *polarbear);

#endif
