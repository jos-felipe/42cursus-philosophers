/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/08 11:58:54 by josfelip         ###   ########.fr       */
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
	// t_philo			philo;
	unsigned	args[N_ARGS];
	unsigned	u;
	pthread_t	**_threads;
	int			result_code;

	// philo_init(&philo);
	philo_startup(args);
	philo_validate_argc(argc);
	// philo_validate_argv(argc, argv, &philo);
	philo_validate_argv_(argc, argv);
	philo_assignment_args(argc, argv, args);
	_threads = (pthread_t **)malloc(args[PHILOSOPHERS] * sizeof(pthread_t *));
	u = 0;
	while (u < args[PHILOSOPHERS])
	{
		_threads[u] = (pthread_t *)malloc(sizeof(pthread_t));
		printf("In main: Creating philosopher %u.\n", u);
		result_code = pthread_create(_threads[u], NULL, perform_task, &u);
		assert(!result_code);
		u++;
	}
	printf("In main: All philosophers are created.\n");
	
	u = 0;
	while (u < args[PHILOSOPHERS])
	{
		result_code = pthread_join(*_threads[u], NULL);
		assert(!result_code);
		printf("In main: Philosopher %u has died.\n", u);
		free(_threads[u]);
		u++;
	}
	
	printf("Main program has ended.\n");
	free(_threads);
	return (0);
}
