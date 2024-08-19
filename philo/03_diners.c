/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_diners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/19 09:49:50 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_printf(char *state_fmt, t_diner *philo, \
unsigned int u)
{
	int	ts;

	// pthread_mutex_lock(philo->mutex);
	ts = (int)philo_get_timestamp_in_ms(philo->diner_start);
	printf(state_fmt, ts, u);
	// pthread_mutex_unlock(philo->mutex);
}

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

void	philo_eat_sleep_think(t_diner *philo, \
unsigned int u, unsigned int next)
{
	int	ts;

	pthread_mutex_lock(&philo->forks_state[u - 1]);
	pthread_mutex_lock(&philo->forks_state[next - 1]);
	// pthread_mutex_lock(philo->mutex);
	ts = (int)philo_get_timestamp_in_ms(philo->diner_start);
	printf("%d %u has taken a fork\n", ts, u);
	ts = (int)philo_get_timestamp_in_ms(philo->diner_start);
	philo->next_meal_in_ms = philo_update_next_meal(ts, philo->diet);
	printf("%d %u is eating\n", ts, u);
	// pthread_mutex_unlock(philo->mutex);
	usleep(philo->diet[TIME_TO_EAT] * 1000);
	pthread_mutex_unlock(&philo->forks_state[next - 1]);
	pthread_mutex_unlock(&philo->forks_state[u - 1]);
	if (philo->open_buffet == 0)
		philo->diet[MEALS] -= 1;
	philo_printf("%d %u is sleeping\n", philo, u);
	usleep(philo->diet[TIME_TO_SLEEP] * 1000);
	philo_printf("%d %u is thinking\n", philo, u);
}
