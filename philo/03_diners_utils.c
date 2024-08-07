/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_diners_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/07 16:31:03 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_diners_all_you_can_eat(void *arguments)
{
	t_diner			*philo;
	unsigned int	u;
	unsigned int	next;

	philo = (t_diner *)arguments;
	u = philo->diner_id + 1;
	next = u % philo->diet[PHILOSOPHERS] + 1;
	philo_printf("%f %u is sleeping\n", philo, u);
	if (u % 2 == 0)
		usleep(philo->diet[TIME_TO_EAT] * 1000);
	while (42)
	{
		pthread_mutex_lock(philo->mutex);
		if (*philo->exit_signal)
		{
			pthread_mutex_unlock(philo->mutex);
			break ;
		}
		else
		{
			philo_timestamp_eat_sleep_think(philo, u, next);
			pthread_mutex_unlock(philo->mutex);
		}
	}
	return (NULL);
}
