/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_diners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/06 15:34:39 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	philo_timestamp_ms(struct timeval meal_start)
{
	double			t0;
	double			t1;
	struct timeval	tv;

	t0 = (double)meal_start.tv_sec * (double)1000;
	t0 += (double)meal_start.tv_usec / (double)1000;
	assert(!gettimeofday(&tv, NULL));
	t1 = (double)tv.tv_sec * (double)1000;
	t1 += (double)tv.tv_usec / (double)1000;
	return (t1 - t0);
}

void	philo_timestamp_eat_sleep_think(t_diner *philo, \
unsigned int u, unsigned int next)
{
	if (philo->forks[u - 1] && philo->forks[next - 1])
	{
		philo->forks[u - 1] = 0;
		philo->forks[next - 1] = 0;
		printf("%f %u has taken a fork\n", \
		philo_timestamp_ms(philo->meal_start), u);
		printf("%f %u is eating\n", philo_timestamp_ms(philo->meal_start), u);
		usleep(philo->diet[TIME_TO_EAT] * 1000);
		philo->forks[u - 1] = 1;
		philo->forks[next - 1] = 1;
		assert(!gettimeofday(&philo->last_meal[u - 1], NULL));
		pthread_mutex_unlock(philo->mutex);
		if (philo->diet[MEALS])
			philo->diet[MEALS] -= 1;
		printf("%f %u is sleeping\n", philo_timestamp_ms(philo->meal_start), u);
		usleep(philo->diet[TIME_TO_SLEEP] * 1000);
		printf("%f %u is thinking\n", philo_timestamp_ms(philo->meal_start), u);
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
	pthread_mutex_lock(philo->mutex);
	printf("%f %u is thinking\n", philo_timestamp_ms(philo->meal_start), u);
	pthread_mutex_unlock(philo->mutex);
	if (u % 2 == 0)
		usleep(philo->diet[TIME_TO_EAT] * 1000);
	pthread_mutex_lock(philo->mutex);
	while (!philo->diet[MEALS] && !*philo->exit_signal)
		philo_timestamp_eat_sleep_think(philo, u, next);
	while (philo->diet[MEALS] && !*philo->exit_signal)
		philo_timestamp_eat_sleep_think(philo, u, next);
	return (NULL);
}