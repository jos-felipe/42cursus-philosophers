/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_start_the_meal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/15 11:03:13 by josfelip         ###   ########.fr       */
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
	while (philo->forks[u - 1] && philo->forks[next - 1])
	{
		philo->forks[u - 1] = 0;
		philo->forks[next - 1] = 0;
		printf("P%u: I toke my fork and the one of P%u.\n", u, next);
		sleep(3);
		philo->forks[u - 1] = 1;
		philo->forks[next - 1] = 1;
		printf("P%u: I released my fork and the one of P%u.\n", u, next);
		sleep(3);
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
	while (philo->forks[u - 1] && philo->forks[next - 1] && \
	philo->diet[MEALS])
	{
		philo->forks[u - 1] = 0;
		philo->forks[next - 1] = 0;
		printf("P%u: I toke my fork and the one of P%u.\n", u, next);
		sleep(3);
		philo->forks[u - 1] = 1;
		philo->forks[next - 1] = 1;
		philo->diet[MEALS] -= 1;
		printf("P%u: I released my fork and the one of P%u.\n", u, next);
		sleep(3);
	}
	return (NULL);
}
