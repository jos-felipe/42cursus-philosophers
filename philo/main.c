/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/03 11:50:36 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo)
{
	philo->number_of_philosophers = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->number_of_times_each_philosopher_must_eat = 0;
}

void	philo_debug(t_philo	*philo)
{	
	printf("philo->number_of_philosophers = %u\n", philo->number_of_philosophers);
	printf("philo->time_to_die = %u\n", philo->time_to_die);
	printf("philo->time_to_eat = %u\n", philo->time_to_eat);
	printf("philo->time_to_sleep = %u\n", philo->time_to_sleep);
	printf("philo->number_of_times_each_philosopher_must_eat = %u\n", philo->number_of_times_each_philosopher_must_eat);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	
	philo_init(&philo);
	philo_debug(&philo);
	philo_validate_argc(argc);
	printf("name: %s\n", argv[0]);
	return (0);
}
