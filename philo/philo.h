/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:32:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/10 13:46:24 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <assert.h>

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
# define TIME_TO_DIE 0
# define TIME_TO_EAT 1
# define TIME_TO_SLEEP 2
# define MEALS 3

# define NUM_THREADS 5

typedef struct s_philo
{
	pthread_t	**threads;
}				t_philo;


typedef struct s_diner
{
	unsigned int	diner_id;
	unsigned int	diet[N_ARGS - 1];
	int				*forks;
	pthread_t		diner;
}				t_diner;

typedef struct s_host
{
	unsigned int	seats;
	int				*forks;
	t_diner			*list_of_diners;
}				t_host;
// 01_args.c
void			philo_validate_argc(int argc);
void			philo_validate_argv(int argc, char *argv[]);
void			philo_assignment_args(int argc, char *argv[], \
				unsigned int *args);

// 01_args_utils.c
unsigned int	ft_atou(const char *nptr);

// 02_philo_to_data.c
void			philo_allocation(t_philo *data, unsigned int *args);
void			philo_dallocation(t_philo *data, unsigned int n);
void			philo_fill_the_list_of_diners(t_host *host, unsigned int n);
void			philo_set_the_table(t_host *host, unsigned int *args);
void			philo_start_feeding(t_host *spaghetti, unsigned int n);



#endif
