/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_buffet_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/19 12:11:51 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_set_diner_diet(t_diner *philo, \
int *args);

void	philo_buffet_newdiner(t_buffet *host, \
int *args, int u)
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

double	philo_update_next_meal(double last_meal_in_ms, int *diet)
{
	double	next_meal_in_ms;

	next_meal_in_ms = last_meal_in_ms;
	next_meal_in_ms += (double)diet[TIME_TO_DIE];
	return (next_meal_in_ms);
}

int	philo_memcheck(void *ptr)
{
	int	status;

	status = 0;
	if (!ptr)
	{
		printf("fatal: unable to allocate memory");
		status = 1;
	}
	return (status);
}

static void	philo_set_diner_diet(t_diner *philo, \
int *args)
{
	int	u;

	u = 0;
	while (u < N_ARGS)
	{
		philo->diet[u] = args[u];
		u++;
	}
}
