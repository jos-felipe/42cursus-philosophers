/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:32:04 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/03 10:22:37 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define PHILO_ARGS "info: ./philo \
number_of_philosophers \
time_to_die (in milliseconds) \
time_to_eat (in milliseconds) \
time_to_sleep (in milliseconds) \
[number_of_times_each_philosopher_must_eat]\n"
# define PHILO_FATAL_ERROR "fatal: invalid argument(s)\n"

typedef struct	s_philo
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;

}				t_philo;

void	philo_validate_user_inputs(int argc, char *argv[]);

#endif