/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_diners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/07 13:49:20 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	philo_get_timestamp_in_ms(struct timeval tic)
{
	double			tic_toc;
	struct timeval	toc;

	assert(!gettimeofday(&toc, NULL));
	tic_toc = (double)(toc.tv_sec - tic.tv_sec);
	tic_toc *= 1000.0;
	tic_toc += (double)(toc.tv_usec) / 1000.0;
	tic_toc -= (double)(tic.tv_usec) / 1000.0;
	return (tic_toc);
}

void	philo_timestamp_eat_sleep_think(t_diner *philo, \
unsigned int u, unsigned int next)
{
	double	toc;
	
	if (philo->forks[u - 1] && philo->forks[next - 1])
	{
		philo->forks[u - 1] = 0;
		philo->forks[next - 1] = 0;
		toc = philo_get_timestamp_in_ms(philo->diner_start);
		printf("%f %u has taken a fork\n", toc, u);
		toc = philo_get_timestamp_in_ms(philo->diner_start);
		philo->next_meal_in_ms = philo_update_next_meal_time(toc, philo->diet) + (double)philo->diet[TIME_TO_EAT];
		printf("%f %u is eating\n", toc, u);
		pthread_mutex_unlock(philo->mutex);
		usleep(philo->diet[TIME_TO_EAT] * 1000);
		pthread_mutex_lock(philo->mutex);
		philo->forks[u - 1] = 1;
		philo->forks[next - 1] = 1;
		if (philo->diet[MEALS])
			philo->diet[MEALS] -= 1;
		pthread_mutex_unlock(philo->mutex);
		printf("%f %u is sleeping\n", philo_get_timestamp_in_ms(philo->diner_start), u);
		usleep(philo->diet[TIME_TO_SLEEP] * 1000);
		printf("%f %u is thinking\n", philo_get_timestamp_in_ms(philo->diner_start), u);
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
	printf("%f %u is thinking\n", philo_get_timestamp_in_ms(philo->diner_start), u);
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
