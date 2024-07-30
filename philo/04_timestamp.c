/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_timestamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/30 16:10:50 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	philo_seconds(struct timeval meal_start)
{
	long int	timestamp;
	
	timestamp = (long int)meal_start.tv_sec;
	return (timestamp);
}

static long int	philo_useconds(struct timeval meal_start)
{
	long int	timestamp;
	
	timestamp = (long int)meal_start.tv_usec;
	return (timestamp);
}

void			philo_timestamp_eat_sleep_think(t_diner *philo, \
unsigned int u, unsigned int next)
{
	philo->forks[u - 1] = 0;
	philo->forks[next - 1] = 0;
	printf("%ld.%ld %u has taken a fork\n", philo_seconds(philo->meal_start), philo_useconds(philo->meal_start) , u);
	printf("%ld.%ld %u is eating\n", philo_seconds(philo->meal_start), philo_useconds(philo->meal_start) , u);
	usleep(philo->diet[TIME_TO_EAT] * 1000);
	philo->forks[u - 1] = 1;
	philo->forks[next - 1] = 1;
	if (philo->diet[MEALS])
		philo->diet[MEALS] -= 1;
	printf("%ld.%ld %u is sleeping\n", philo_seconds(philo->meal_start), philo_useconds(philo->meal_start) , u);
	usleep(philo->diet[TIME_TO_SLEEP] * 1000);
	printf("%ld.%ld %u is thinking\n", philo_seconds(philo->meal_start), philo_useconds(philo->meal_start) , u);
}
