/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/19 10:43:59 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_startup(U_INT *args)
{
	int	i;

	i = -1;
	while (++i < N_ARGS)
		args[i] = 0;
}

int	main(int argc, char *argv[])
{
	t_buffet			spaghetti;
	U_INT		args[N_ARGS];

	philo_startup(args);
	if (argc < 5 || argc > 6)
	{
		printf(PHILO_FATAL_ERROR);
		printf(PHILO_ARGS);
		return (1);
	}
	if (philo_validate_argv(argc, argv))
		return (1);
	philo_assignment_args(argc, argv, args);
	if (args[PHILOSOPHERS] == 1)
		philo_one_diner(args[TIME_TO_DIE]);
	else
	{
		philo_fill_the_list_of_diners(&spaghetti, args);
		philo_buffet_preparation(&spaghetti);
		philo_buffet_set_the_table(&spaghetti, args);
		philo_buffet_closing(&spaghetti);
	}
	return (0);
}
