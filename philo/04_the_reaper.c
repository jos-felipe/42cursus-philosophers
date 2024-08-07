/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_the_reaper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/07 11:06:21 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_the_reaper_scythe(t_buffet *host)
{
	double			t0;
	double			t1;
	struct timeval	tv;
	unsigned int	u;

	assert(!gettimeofday(&tv, NULL));
	t0 = (double)tv.tv_sec * (double)1000;
	t0 += (double)tv.tv_usec / (double)1000;
	u = 0;
	while (u < host->seats)
	{
		t1 = host->list_of_diners[u].next_meal;
		if (t1 < t0)
		{
			printf("%f %u died\n", philo_get_timestamp_ms(host->diner_start), u + 1);
			host->exit_signal = 1;
			break ;
		}
		u++;
	}
	return (t1 < t0);
}

void		*philo_the_reaper_service(void *arguments)
{
	t_buffet	*host;
	
	host = (t_buffet *)arguments;
	while (42)
	{
		pthread_mutex_lock(host->mutex);
		if (host->exit_signal)
		{
			pthread_mutex_unlock(host->mutex);
			break ;
		}
		else
		{
			philo_the_reaper_scythe(host);
			pthread_mutex_unlock(host->mutex);
		}
	}
	pthread_mutex_destroy(host->mutex);
	free(host->forks);
	free(host->list_of_diners);
	free(host->mutex);
	return (NULL);
}
