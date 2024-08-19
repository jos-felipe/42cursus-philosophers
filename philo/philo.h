/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:32:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/19 10:47:55 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <assert.h>
# include <sys/time.h>

# define PHILO_FATAL_ERROR "fatal: invalid number of arguments\n"
# define PHILO_ARGS "info: ./philo \
number_of_philosophers \
time_to_die (in milliseconds) \
time_to_eat (in milliseconds) \
time_to_sleep (in milliseconds) \
[number_of_times_each_philosopher_must_eat]\n"

# define OUT_OF_BOUNDS_FATAL "fatal: arg number %d is out of bounds.\n"
# define OUT_OF_BOUNDS_INFO "info: %s must be greater than zero\n"

# define N_ARGS 5
# define PHILOSOPHERS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define MEALS 4

# define U_INT unsigned int

typedef struct s_diner
{
	char			*exit_signal;
	char			open_buffet;
	double			next_meal_in_ms;
	pthread_mutex_t	*forks_state;
	pthread_mutex_t	*mutex;
	pthread_t		diner;
	struct timeval	diner_start;
	U_INT			diet[N_ARGS];
	U_INT			diner_id;
}				t_diner;

typedef struct s_buffet
{
	char			exit_signal;
	char			open_buffet;
	pthread_mutex_t	*forks_state;
	pthread_mutex_t	*mutex;
	pthread_t		reaper;
	struct timeval	diner_start;
	t_diner			*list_of_diners;
	U_INT			seats;
}				t_buffet;

// 01_args.c
int				philo_validate_argv(int argc, char *argv[]);
void			philo_assignment_args(int argc, char *argv[], \
				U_INT *args);

// 01_args_utils.c
U_INT			ft_atou(const char *nptr);

// 02_buffet.c
void			philo_buffet_preparation(t_buffet *host);
void			philo_buffet_set_the_table(t_buffet *host, U_INT *args);
void			philo_buffet_closing(t_buffet *host);
void			philo_fill_the_list_of_diners(t_buffet *host, U_INT *args);
void			philo_one_diner(U_INT time_to_die);

// 02_buffet_utils.c
double			philo_update_next_meal(double toc, U_INT *diet);
void			philo_memcheck(void *ptr);
void			philo_buffet_newdiner(t_buffet *host, \
U_INT *args, U_INT u);

// 03_diners.c
double			philo_get_timestamp_in_ms(struct timeval tic);
void			philo_eat_sleep_think(t_diner *philo, \
U_INT u, U_INT next);
void			philo_printf(char *state_fmt, t_diner *philo, \
U_INT u);

// 03_diners_utils.c
void			*philo_diners_service(void *arguments);

// 04_the_reaper.c
void			*philo_the_reaper_service(void *arguments);

#endif
