/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/08 11:35:06 by josfelip         ###   ########.fr       */
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
	t_philo			philo;
	unsigned int	args[N_ARGS];
	pthread_t		threads[NUM_THREADS];
	pthread_t		**_threads;
	int				thread_args[NUM_THREADS];
	int				i;
	int				result_code;

	philo_init(&philo);
	philo_startup(args);
	philo_validate_argc(argc);
	philo_validate_argv(argc, argv, &philo);
	philo_validate_argv_(argc, argv);
	_threads = (pthread_t **)malloc(philo.args[0] * sizeof(pthread_t *));
	i = -1;
	while (++i < (int)philo.args[PHILOSOPHERS])
	{
		printf("In main: Creating thread %d.\n", i);
		thread_args[i] = i;
		result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
		assert(!result_code);
		_threads[i] = (pthread_t *)malloc(sizeof(pthread_t));
		printf("In main: Creating philosopher %d.\n", i);
		result_code = pthread_create(_threads[i], NULL, perform_task, &i);
		assert(!result_code);

	}
	printf("In main: All threads are created.\n");
	printf("In main: All philosophers are created.\n");
	
	i = -1;
	while (++i < (int)philo.args[0])
	{
		result_code = pthread_join(threads[i], NULL);
		assert(!result_code);
		printf("In main: Thread %d has ended.\n", i);
		result_code = pthread_join(*_threads[i], NULL);
		assert(!result_code);
		printf("In main: Philosopher %d has died.\n", i);
		free(_threads[i]);
	}
	
	printf("Main program has ended.\n");
	free(_threads);
	return (0);
}
