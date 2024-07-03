/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/03 10:50:32 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**philo_getadd(void)
{
	static t_philo	*philo;
	
	return(&philo);
}

void	philo_init(void)
{
	t_philo	*philo;
	
	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->number_of_philosophers = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->number_of_times_each_philosopher_must_eat = 0;
	*(philo_getadd()) = philo;
}
void	philo_debug(void)
{
	t_philo	*philo;
	
	philo = *(philo_getadd());
	printf("philo->number_of_philosophers = %u\n", philo->number_of_philosophers);
	printf("philo->time_to_die = %u\n", philo->time_to_die);
	printf("philo->time_to_eat = %u\n", philo->time_to_eat);
	printf("philo->time_to_sleep = %u\n", philo->time_to_sleep);
	printf("philo->number_of_times_each_philosopher_must_eat = %u\n", philo->number_of_times_each_philosopher_must_eat);
}

int	main(int argc, char *argv[])
{
	philo_init();
	philo_debug();
	philo_validate_user_inputs(argc, argv);
	return (0);
}
