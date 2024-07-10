/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_philo_to_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/10 13:50:17 by josfelip         ###   ########.fr       */
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
	int				index;
	int				sleep_time;
	unsigned int	*args;

	args = (unsigned *)arguments;
	index = 1 + rand() % args[PHILOSOPHERS];
	sleep_time = 1 + rand() % args[PHILOSOPHERS];
	printf("_Philosopher %d: Eaten.\n", index);
	printf("_Philosopher %d: Will be sleeping for %d seconds.\n", index, \
	sleep_time);
	sleep(sleep_time);
	printf("_Philosopher %d: Died.\n", index);
	return (NULL);
}

static void	*philo_take_a_seat(void *arguments)
{
	t_diner			*philo;

	philo = (t_diner *)arguments;
	printf("P%u: Hi, I'm Philosopher %u!\n",  philo->diner_id, philo->diner_id);
	printf("P%u: I'll die if I wait more than %u ms to eat.\n", philo->diner_id, philo->diet[TIME_TO_DIE]);
	printf("P%u: I take %u ms to eat.\n", philo->diner_id, philo->diet[TIME_TO_EAT]);
	printf("P%u: Then I sleep for %u ms.\n", philo->diner_id, philo->diet[TIME_TO_SLEEP]);
	printf("P%u: I'll take %u meals before I leave the table.\n", philo->diner_id, philo->diet[MEALS]);
	return (NULL);
}

static void	philo_set_diner_diet(t_diner *philo, \
unsigned int *args)
{
	unsigned int	u;

	u = 1;
	while (u < N_ARGS)
	{
		philo->diet[u - 1] = args[u];
		u++;
	}
}

void	philo_allocation(t_philo *data, unsigned int *args)
{
	unsigned int	u;
	int				result_code;

	data->threads = (pthread_t **)malloc(args[PHILOSOPHERS] * \
	sizeof(pthread_t *));
	philo_memcheck(data->threads);
	u = 0;
	while (u < args[PHILOSOPHERS])
	{
		data->threads[u] = (pthread_t *)malloc(sizeof(pthread_t));
		printf("In main: Creating philosopher %u.\n", u);
		result_code = pthread_create(data->threads[u], NULL, \
		_perform_task, args);
		assert(!result_code);
		u++;
	}
	// pthread_self();
}

void	philo_dallocation(t_philo *data, unsigned int n)
{
	unsigned int	u;
	int				result_code;

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

void	philo_fill_the_list_of_diners(t_host *host, unsigned int n)
{
	if (n < 2)
	{
		printf("fatal: number of philosophers must be greater than one");
		exit(EXIT_FAILURE);
	}
	host->seats = n;
	host->list_of_diners = (t_diner *)malloc(n * sizeof(t_diner));
	philo_memcheck(host->list_of_diners);
}

void	philo_set_the_table(t_host *host, \
unsigned int *args)
{
	unsigned int	u;
	int				result_code;

	host->forks = (int *)malloc(host->seats * sizeof(int));
	philo_memcheck(host->forks);
	u = 0;
	while (u < host->seats)
	{
		host->list_of_diners[u].diner_id = u;
		result_code = pthread_create(&host->list_of_diners[u].diner, \
		NULL, philo_take_a_seat, &host->list_of_diners[u]);
		assert(!result_code);
		host->forks[u] = 1;
		host->list_of_diners[u].forks = host->forks;
		philo_set_diner_diet(&host->list_of_diners[u], \
		args);
		u++;
	}
}

void	philo_start_feeding(t_host *spaghetti, unsigned int n)
{
	unsigned int	u;
	int				result_code;

	u = 0;
	while (u < n)
	{
		result_code = pthread_join(spaghetti->list_of_diners[u].diner, NULL);
		assert(!result_code);
		u++;
	}
	free(spaghetti->forks);
	free(spaghetti->list_of_diners);
}
