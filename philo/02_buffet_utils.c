/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_buffet_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/07 11:56:43 by josfelip         ###   ########.fr       */
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
static double	philo_timeval_to_ms(struct timeval tic)
{
	double			t0;
	double			t1;
	struct timeval	toc;

	t0 = (double)tic.tv_sec * (double)1000;
	t0 += (double)tic.tv_usec / (double)1000;
	assert(!gettimeofday(&toc, NULL));
	t1 = (double)toc.tv_sec * (double)1000;
	t1 += (double)toc.tv_usec / (double)1000;
	return (t1 - t0);
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
	host->list_of_diners[u].diner_id = u;
	host->list_of_diners[u].exit_signal = &host->exit_signal;
	host->list_of_diners[u].forks = host->forks;
	host->list_of_diners[u].next_meal = philo_timeval_to_ms(host->diner_start) + \
	(double)args[TIME_TO_DIE];
	host->list_of_diners[u].diner_start = host->diner_start;
	host->list_of_diners[u].mutex = host->mutex;
	philo_set_diner_diet(&host->list_of_diners[u], args);
}
