/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_buffet_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/05 13:43:24 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_set_diner_diet(t_diner *philo, \
unsigned int *args)
{
	unsigned int	u;

	u = 0;
	while (u < N_ARGS)
	{
		philo->diet[u] = args[u];
		u++;
	}
}

void	philo_memcheck(void *ptr)
{
	if (!ptr)
	{
		printf("fatal: unable to allocate memory");
		exit(EXIT_FAILURE);
	}
}

void	philo_buffet_newdiner(t_buffet *host, \
unsigned int *args, unsigned int u)
{
	host->list_of_diners[u].diner_id = u;
	philo_set_diner_diet(&host->list_of_diners[u], args);
	host->list_of_diners[u].forks = host->forks;
	host->list_of_diners[u].meal_start = host->meal_start;
	host->list_of_diners[u].mutex = host->mutex;
}

void	*philo_buffet_service(void *arguments)
{
	t_diner			*philo;
	unsigned int	u;
	unsigned int	next;

	philo = (t_diner *)arguments;
	u = philo->diner_id + 1;
	next = u % philo->diet[PHILOSOPHERS] + 1;
	pthread_mutex_lock(philo->mutex);
	printf("%f %u is thinking\n", philo_timestamp_ms(philo->meal_start), u);
	pthread_mutex_unlock(philo->mutex);
	if (u % 2 == 0)
		usleep(philo->diet[TIME_TO_EAT] * 1000);
	while (!philo->diet[MEALS])
		philo_timestamp_eat_sleep_think(philo, u, next);
	while (philo->diet[MEALS])
		philo_timestamp_eat_sleep_think(philo, u, next);
	return (NULL);
}
