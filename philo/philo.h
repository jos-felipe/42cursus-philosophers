/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:32:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/03 13:49:49 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define PHILO_FATAL_ERROR "fatal: invalid number of argument(s)\n"
# define PHILO_ARGS "info: ./philo \
number_of_philosophers \
time_to_die (in milliseconds) \
time_to_eat (in milliseconds) \
time_to_sleep (in milliseconds) \
[number_of_times_each_philosopher_must_eat]\n"

# define OUT_OF_BOUNDS_FATAL "fatal: out of bounds input(s)\n"
# define OUT_OF_BOUNDS_INFO "info: inputs must be greater than zero\n"

# define N_ARGS 5

typedef struct	s_philo
{
	unsigned int	args[N_ARGS];

}				t_philo;

void	philo_validate_argc(int argc);
void	philo_validate_argv(int argc, char *argv[], 
t_philo *philo);

#endif