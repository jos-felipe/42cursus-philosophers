/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/05 11:35:04 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < N_ARGS)
		philo->args[i] = 0;
}

void	philo_debug(t_philo	*philo)
{
	int	i;

	i = -1;
	while (++i < N_ARGS)
		printf("philo->args[%d] = %u\n", i, philo->args[i]);
}

void	*perform_work(void *arguments)
{
	int	index = *((int *)arguments);
	int sleep_time = 1 + rand() % NUM_THREADS;

	printf("Thread %d: Started.\n", index);
	printf("Thread %d: Will be sleeping for %d seconds.\n", index, sleep_time);
	sleep(sleep_time);
	printf("Thread %d: Ended.\n", index);
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	pthread_t	threads[NUM_THREADS];
	int			thread_args[NUM_THREADS];
	int			i;
	int			result_code;

	philo_init(&philo);
	philo_validate_argc(argc);
	philo_validate_argv(argc, argv, &philo);
	i = -1;
	while (++i < NUM_THREADS)
	{
		printf("In main: Creating thread %d.\n", i);
		thread_args[i] = i;
		result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
		assert(!result_code);
	}
	printf("In main: All threads are created.\n");
	
	i = -1;
	while (++i < NUM_THREADS)
	{
		printf("In main: Creating thread %d.\n", i);
		thread_args[i] = i;
		result_code = pthread_join(threads[i], NULL);
		assert(!result_code);
		printf("In main: Thread %d has ended.\n", i);
	}
	
	printf("Main program has ended.\n");
	return (0);
}
