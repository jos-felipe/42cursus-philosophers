/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_timestamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/29 16:37:53 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_timestamp_eat_sleep_think(t_diner *philo, unsigned int u, \
unsigned int next, long meal_start)
{
	philo->forks[u - 1] = 0;
	philo->forks[next - 1] = 0;
	printf("%ld %u has taken a fork\n", philo_timestamp(meal_start), u);
	printf("%u is eating\n", u);
	usleep(philo->diet[TIME_TO_EAT] * 1000);
	philo->forks[u - 1] = 1;
	philo->forks[next - 1] = 1;
	if (philo->diet[MEALS])
		philo->diet[MEALS] -= 1;
	printf("%u is sleeping\n", u);
	usleep(philo->diet[TIME_TO_SLEEP] * 1000);
	printf("%u is thinking\n", u);
}

void	*philo_all_you_can_eat(void *arguments)
{
	t_diner			*philo;
	unsigned int	u;
	unsigned int	next;

	philo = (t_diner *)arguments;
	u = philo->diner_id + 1;
	next = u % philo->diet[PHILOSOPHERS] + 1;
	printf("%u is thinking\n", u);
	if (u % 2 == 0)
		usleep(philo->diet[TIME_TO_EAT] * 1000);
	while (42)
	{
		if (philo->forks[u - 1] && philo->forks[next - 1])
			philo_eat_sleep_think(philo, u, next);
	}
	return (NULL);
}

void	*philo_a_la_carte(void *arguments)
{
	t_diner			*philo;
	unsigned int	u;
	unsigned int	next;

	philo = (t_diner *)arguments;
	u = philo->diner_id + 1;
	next = u % philo->diet[PHILOSOPHERS] + 1;
	printf("%u is thinking\n", u);
	if (u % 2 == 0)
		usleep(philo->diet[TIME_TO_EAT] * 1000);
	while (philo->diet[MEALS])
	{
		if (philo->forks[u - 1] && philo->forks[next - 1])
			philo_eat_sleep_think(philo, u, next);
	}
	return (NULL);
}
