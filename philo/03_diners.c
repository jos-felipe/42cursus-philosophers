/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_diners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/07 13:03:03 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	philo_get_timestamp_in_sec(struct timeval tic)
{
	double			t0;
	double			t1;
	struct timeval	toc;

	t0 = (double)tic.tv_sec * (double)1000;
	t0 += (double)tic.tv_usec / (double)1000;
	assert(!gettimeofday(&toc, NULL));
	t1 = (double)toc.tv_sec * (double)1000;
	t1 += (double)toc.tv_usec / (double)1000;
	return (t1 - t0);
}

void	philo_timestamp_eat_sleep_think(t_diner *philo, \
unsigned int u, unsigned int next)
{
	double	toc;
	
	if (philo->forks[u - 1] && philo->forks[next - 1])
	{
		philo->forks[u - 1] = 0;
		philo->forks[next - 1] = 0;
		toc = philo_get_timestamp_in_sec(philo->diner_start);
		printf("%f %u has taken a fork\n", toc, u);
		toc = philo_get_timestamp_in_sec(philo->diner_start);
		philo->next_meal = philo_set_next_meal_time(toc, philo->diet);
		printf("%f %u is eating\n", toc, u);
		pthread_mutex_unlock(philo->mutex);
		usleep(philo->diet[TIME_TO_EAT] * 1000);
		pthread_mutex_lock(philo->mutex);
		philo->forks[u - 1] = 1;
		philo->forks[next - 1] = 1;
		if (philo->diet[MEALS])
			philo->diet[MEALS] -= 1;
		pthread_mutex_unlock(philo->mutex);
		printf("%f %u is sleeping\n", philo_get_timestamp_in_sec(philo->diner_start), u);
		usleep(philo->diet[TIME_TO_SLEEP] * 1000);
		printf("%f %u is thinking\n", philo_get_timestamp_in_sec(philo->diner_start), u);
		pthread_mutex_lock(philo->mutex);
	}
}

void	*philo_diners_service(void *arguments)
{
	t_diner			*philo;
	unsigned int	u;
	unsigned int	next;

	philo = (t_diner *)arguments;
	u = philo->diner_id + 1;
	next = u % philo->diet[PHILOSOPHERS] + 1;
	printf("%f %u is thinking\n", philo_get_timestamp_in_sec(philo->diner_start), u);
	if (u % 2 == 0)
		usleep(philo->diet[TIME_TO_EAT] * 1000);
	while (philo->diet[MEALS])
	{
		pthread_mutex_lock(philo->mutex);
		if (*philo->exit_signal)
		{
			pthread_mutex_unlock(philo->mutex);
			break ;
		}
		else
		{
			philo_timestamp_eat_sleep_think(philo, u, next);
			pthread_mutex_unlock(philo->mutex);
		}
	}
	return (NULL);
}
