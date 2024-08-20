/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_the_reaper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/20 09:41:55 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_the_reaper_scythe(t_buffet *host);

void	*philo_the_reaper_service(void *arguments)
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
	return (NULL);
}

static void	philo_the_reaper_scythe(t_buffet *host)
{
	double	t0;
	double	t1;
	int		ts;
	int		u;

	t0 = philo_get_timestamp_in_ms(host->diner_start);
	u = 0;
	while (u < host->seats)
	{
		t1 = host->list_of_diners[u].next_meal_in_ms;
		if (t1 == 0)
			t1 = t0;
		if (t1 < t0)
		{
			ts = (int)philo_get_timestamp_in_ms(host->diner_start);
			printf("%d %u died\n", ts, u + 1);
			host->exit_signal = 1;
			break ;
		}
		u++;
	}
}
