/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_philo_to_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/08 13:34:37 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_memcheck(void *ptr)
{
	if (!ptr)
	{
		printf("fatal: unable to allocate memory");
		exit(EXIT_FAILURE);	
	}
}

static void	*_perform_task(void *arguments)
{
	int			index;
	int 		sleep_time;
	unsigned	*args;
	

	args = (unsigned *)arguments;
	index = 1 + rand() % args[PHILOSOPHERS];
	sleep_time = 1 + rand() % args[PHILOSOPHERS];
	printf("_Philosopher %d: Eaten.\n", index);
	printf("_Philosopher %d: Will be sleeping for %d seconds.\n", index, sleep_time);
	sleep(sleep_time);
	printf("_Philosopher %d: Died.\n", index);
	return NULL;
}

void	philo_allocation(t_philo *data, unsigned *args)
{
	unsigned	u;
	int			result_code;
	
	data->threads = (pthread_t **)malloc(args[PHILOSOPHERS] * sizeof(pthread_t *));
	philo_memcheck(data->threads);
	u = 0;
	while (u < args[PHILOSOPHERS])
	{
		data->threads[u] = (pthread_t *)malloc(sizeof(pthread_t));
		printf("In main: Creating philosopher %u.\n", u);
		result_code = pthread_create(data->threads[u], NULL, _perform_task, args);
		assert(!result_code);
		u++;
	}
}

void	philo_dallocation(t_philo *data, unsigned n)
{
	unsigned	u;
	int			result_code;
	
	u = 0;
	while (u < n)
	{
		result_code = pthread_join(*data->threads[u], NULL);
		assert(!result_code);
		printf("In main: Philosopher %u has died.\n", u);
		free(data->threads[u]);
		u++;
	}
	free(data->threads);
}