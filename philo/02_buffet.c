/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_buffet.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/06 14:32:03 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fill_the_list_of_diners(t_buffet *host, unsigned int n)
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

void	philo_buffet_preparation(t_buffet *host)
{
	unsigned int	u;

	host->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo_memcheck(host->mutex);
	pthread_mutex_init(host->mutex, NULL);
	host->forks = (int *)malloc(host->seats * sizeof(int));
	philo_memcheck(host->forks);
	host->last_meal = (struct timeval *)malloc(host->seats * sizeof(struct timeval));
	philo_memcheck(host->last_meal);
	assert(!gettimeofday(&host->meal_start, NULL));
	u = 0;
	while (u < host->seats)
	{
		host->forks[u] = 1;
		host->last_meal[u] = host->meal_start;
		u++;
	}
}

void	philo_set_the_table(t_buffet *host, \
unsigned int *args)
{
	unsigned int	u;
	int				result_code;

	pthread_mutex_lock(host->mutex);
	u = 0;
	while (u < host->seats)
	{
		philo_buffet_newdiner(host, args, u);
		result_code = pthread_create(&host->list_of_diners[u].diner, \
		NULL, philo_diners_service, &host->list_of_diners[u]);
		assert(!result_code);
		u++;
	}
	pthread_mutex_unlock(host->mutex);
	host->time_to_die = args[TIME_TO_DIE];
	host->death_alarm = 0;
	result_code = pthread_create(&host->reaper, \
	NULL, philo_the_reaper_service, host);
	assert(!result_code);
	result_code = pthread_detach(host->reaper);
	assert(!result_code);
}

void	philo_buffet_closing(t_buffet *host)
{
	unsigned int	u;
	int				result_code;

	u = 0;
	while (u < host->seats)
	{
		result_code = pthread_join(host->list_of_diners[u].diner, NULL);
		assert(!result_code);
		u++;
	}
	free(host->forks);
	free(host->list_of_diners);
	pthread_mutex_destroy(host->mutex);
	free(host->mutex);
}
