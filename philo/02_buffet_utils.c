/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_buffet_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/19 10:43:59 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_set_diner_diet(t_diner *philo, \
U_INT *args)
{
	U_INT	u;

	u = 0;
	while (u < N_ARGS)
	{
		philo->diet[u] = args[u];
		u++;
	}
}

double	philo_update_next_meal(double last_meal_in_ms, U_INT *diet)
{
	double	next_meal_in_ms;

	next_meal_in_ms = last_meal_in_ms;
	next_meal_in_ms += (double)diet[TIME_TO_DIE];
	return (next_meal_in_ms);
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
U_INT *args, U_INT u)
{
	host->list_of_diners[u].diner_id = u;
	host->list_of_diners[u].exit_signal = &host->exit_signal;
	host->list_of_diners[u].open_buffet = host->open_buffet;
	host->list_of_diners[u].next_meal_in_ms = (double)args[TIME_TO_DIE];
	host->list_of_diners[u].diner_start = host->diner_start;
	host->list_of_diners[u].mutex = host->mutex;
	host->list_of_diners[u].forks_state = host->forks_state;
	philo_set_diner_diet(&host->list_of_diners[u], args);
}
