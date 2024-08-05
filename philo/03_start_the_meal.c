/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_start_the_meal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/05 11:46:37 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_all_you_can_eat(void *arguments)
{
	t_diner			*philo;
	unsigned int	u;
	unsigned int	next;

	philo = (t_diner *)arguments;
	u = philo->diner_id + 1;
	next = u % philo->diet[PHILOSOPHERS] + 1;
	printf("%f %u is thinking\n", philo_timestamp_ms(philo->meal_start), u);
	if (u % 2 == 0)
		usleep(philo->diet[TIME_TO_EAT] * 1000);
	while (42)
	{
		if (philo->forks[u - 1] && philo->forks[next - 1])
			philo_timestamp_eat_sleep_think(philo, u, next);
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
	printf("%f %u is thinking\n", philo_timestamp_ms(philo->meal_start), u);
	if (u % 2 == 0)
		usleep(philo->diet[TIME_TO_EAT] * 1000);
	while (philo->diet[MEALS])
		philo_timestamp_eat_sleep_think(philo, u, next);
	return (NULL);
}
