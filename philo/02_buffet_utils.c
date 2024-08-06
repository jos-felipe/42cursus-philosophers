/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_buffet_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/06 15:34:39 by josfelip         ###   ########.fr       */
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
	host->list_of_diners[u].exit_signal = &host->exit_signal;
	host->list_of_diners[u].diner_id = u;
	philo_set_diner_diet(&host->list_of_diners[u], args);
	host->list_of_diners[u].forks = host->forks;
	host->list_of_diners[u].last_meal = host->last_meal;
	host->list_of_diners[u].meal_start = host->meal_start;
	host->list_of_diners[u].mutex = host->mutex;
}
