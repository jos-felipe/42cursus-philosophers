/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:32:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/05 14:41:28 by josfelip         ###   ########.fr       */
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
	int				*forks;
	pthread_mutex_t	*mutex;
	pthread_t		diner;
	struct timeval	meal_start;
	unsigned int	diner_id;
	unsigned int	diet[N_ARGS];
}				t_diner;

typedef struct s_buffet
{
	int				*forks;
	pthread_mutex_t	*mutex;
	struct timeval	meal_start;
	t_diner			*list_of_diners;
	unsigned int	seats;
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
void			philo_set_the_table(t_buffet *host, unsigned int *args);
void			philo_buffet_closing(t_buffet *spaghetti, unsigned int n);

// 02_buffet_utils.c
void			philo_memcheck(void *ptr);
void			philo_buffet_newdiner(t_buffet *host, \
unsigned int *args, unsigned int u);
void			*philo_buffet_service(void *arguments);

// 03_diners.c
double			philo_timestamp_ms(struct timeval meal_start);
void			philo_timestamp_eat_sleep_think(t_diner *philo, \
unsigned int u, unsigned int next);

#endif
