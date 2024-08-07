/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:32:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/07 13:08:55 by josfelip         ###   ########.fr       */
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

typedef struct s_diner
{
	char			*exit_signal;
	double			next_meal;
	int				*forks;
	pthread_mutex_t	*mutex;
	pthread_t		diner;
	struct timeval	diner_start;
	unsigned int	diet[N_ARGS];
	unsigned int	diner_id;
}				t_diner;

typedef struct s_buffet
{
	char			exit_signal;
	int				*forks;
	pthread_mutex_t	*mutex;
	pthread_t		reaper;
	struct timeval	diner_start;
	t_diner			*list_of_diners;
	unsigned int	seats;
	unsigned int	time_to_die_in_sec;
}				t_buffet;

// 01_args.c
void			philo_validate_argc(int argc);
void			philo_validate_argv(int argc, char *argv[]);
void			philo_assignment_args(int argc, char *argv[], \
				unsigned int *args);

// 01_args_utils.c
unsigned int	ft_atou(const char *nptr);

// 02_buffet.c
void			philo_fill_the_list_of_diners(t_buffet *host, unsigned int n);
void			philo_buffet_preparation(t_buffet *host);
void			philo_buffet_set_the_table(t_buffet *host, unsigned int *args);
void			philo_buffet_closing(t_buffet *host);

// 02_buffet_utils.c
double			philo_set_next_meal_time(double toc, unsigned int *diet);
void			philo_memcheck(void *ptr);
void			philo_buffet_newdiner(t_buffet *host, \
unsigned int *args, unsigned int u);


// 03_diners.c
void			*philo_diners_service(void *arguments);
double			philo_get_timestamp_in_sec(struct timeval start_time);
void			philo_timestamp_eat_sleep_think(t_diner *philo, \
unsigned int u, unsigned int next);

// 04_the_reaper.c
void			*philo_the_reaper_service(void *arguments);

#endif
