/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_the_reaper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/06 14:29:17 by josfelip         ###   ########.fr       */
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
	pthread_mutex_lock(host->mutex);
	u = 0;
	while (u < host->seats)
	{
		t1 = (double)host->last_meal[u].tv_sec * (double)1000;
		t1 += (double)host->last_meal[u].tv_usec / (double)1000;
		t1 += (double)host->time_to_die;
		if (t1 < t0)
		{
			printf("%f %u died\n", philo_timestamp_ms(host->meal_start), u);
			break ;
		}
		u++;
	}
	pthread_mutex_unlock(host->mutex);
	return ((t1 < t0));
}

void		*philo_the_reaper_service(void *arguments)
{
	t_buffet	*host;
	
	host = (t_diner *)arguments;
	while (42)
	{
		if(philo_the_reaper_scythe(host))
			break ;
	}
	host->death_alarm = 1;
	return (NULL);
}
