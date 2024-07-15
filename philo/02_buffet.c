/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_buffet.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:28 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/15 11:02:52 by josfelip         ###   ########.fr       */
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

void	philo_fill_the_list_of_diners(t_buffet *host, unsigned int n)
{
	if (n < 2)
	{
		printf("fatal: number of philosophers must be greater than one");
		exit(EXIT_FAILURE);
	}
	host->seats = n;
	host->list_of_diners = (t_diner *)malloc(n * sizeof(t_diner));
	philo_memcheck(host->list_of_diners);
}

void	philo_set_the_table(t_buffet *host, \
unsigned int *args)
{
	unsigned int	u;
	int				result_code;
	void			*start_routine;

	host->forks = (int *)malloc(host->seats * sizeof(int));
	philo_memcheck(host->forks);
	u = 0;
	start_routine = philo_all_you_can_eat;
	if (args[MEALS])
		start_routine = philo_a_la_carte;
	while (u < host->seats)
	{
		host->list_of_diners[u].diner_id = u;
		philo_set_diner_diet(&host->list_of_diners[u], args);
		host->forks[u] = 1;
		host->list_of_diners[u].forks = host->forks;
		result_code = pthread_create(&host->list_of_diners[u].diner, \
		NULL, start_routine, &host->list_of_diners[u]);
		assert(!result_code);
		u++;
	}
}

void	philo_start_feeding(t_buffet *spaghetti, unsigned int n)
{
	unsigned int	u;
	int				result_code;

	u = 0;
	while (u < n)
	{
		result_code = pthread_join(spaghetti->list_of_diners[u].diner, NULL);
		assert(!result_code);
		u++;
	}
	free(spaghetti->forks);
	free(spaghetti->list_of_diners);
}
