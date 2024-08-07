/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_buffet_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/07 13:01:55 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		philo_set_diner_diet(t_diner *philo, \
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

double	philo_set_next_meal_time(double toc, unsigned int *diet)
{
	double	next_meal_time;

	next_meal_time = toc;
	next_meal_time += (double)diet[TIME_TO_EAT] / (double)1000;
	next_meal_time += (double)diet[TIME_TO_DIE] / (double)1000;
	return (next_meal_time);
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
	double	toc;
	
	toc = philo_get_timestamp_in_sec(host->diner_start);
	host->list_of_diners[u].diner_id = u;
	host->list_of_diners[u].exit_signal = &host->exit_signal;
	host->list_of_diners[u].forks = host->forks;
	host->list_of_diners[u].next_meal = philo_set_next_meal_time(toc, args);
	host->list_of_diners[u].diner_start = host->diner_start;
	host->list_of_diners[u].mutex = host->mutex;
	philo_set_diner_diet(&host->list_of_diners[u], args);
}
