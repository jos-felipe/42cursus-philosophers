/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/08 13:37:55 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_startup(unsigned int *args)
{
	int	i;

	i = -1;
	while (++i < N_ARGS)
		args[i] = 0;
}

// static void	philo_debug(t_philo	*philo)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < N_ARGS)
// 		printf("philo->args[%d] = %u\n", i, philo->args[i]);
// }

void	*perform_task(void *arguments)
{
	int	index = *((int *)arguments);
	int sleep_time = 1 + rand() % NUM_THREADS;

	printf("Philosopher %d: Eaten.\n", index);
	printf("Philosopher %d: Will be sleeping for %d seconds.\n", index, sleep_time);
	sleep(sleep_time);
	printf("Philosopher %d: Died.\n", index);
	return NULL;
}

int	main(int argc, char *argv[])
{
	unsigned	args[N_ARGS];
	t_philo		data;

	philo_startup(args);
	philo_validate_argc(argc);
	philo_validate_argv(argc, argv);
	philo_assignment_args(argc, argv, args);

	philo_allocation(&data, args);
	philo_dallocation(&data, args[PHILOSOPHERS]);
	
	printf("Main program has ended.\n");
	return (0);
}
