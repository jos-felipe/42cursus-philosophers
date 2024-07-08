/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:32:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/08 13:35:19 by josfelip         ###   ########.fr       */
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
# define NUM_THREADS 5

typedef struct s_philo
{
	pthread_t	**threads;
}				t_philo;

// 01_args.c
void			philo_validate_argc(int argc);
void			philo_validate_argv(int argc, char *argv[]);
void			philo_assignment_args(int argc, char *argv[], unsigned *args);

// 01_args_utils.c
unsigned int	ft_atou(const char *nptr);

// 02_philo_to_data.c
void	philo_allocation(t_philo *data, unsigned *args);
void	philo_dallocation(t_philo *data, unsigned n);

#endif
