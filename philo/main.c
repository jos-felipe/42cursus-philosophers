/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/10 13:46:55 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_startup(unsigned int *args)
{
	int	i;

	i = -1;
	while (++i < N_ARGS)
		args[i] = 0;
}

int	main(int argc, char *argv[])
{
	// t_philo			data;
	t_host				spaghetti;
	unsigned int		args[N_ARGS];

	philo_startup(args);
	philo_validate_argc(argc);
	philo_validate_argv(argc, argv);
	philo_assignment_args(argc, argv, args);
	// philo_allocation(&data, args);
	// philo_dallocation(&data, args[PHILOSOPHERS]);
	// printf("Main program has ended.\n");
	philo_fill_the_list_of_diners(&spaghetti, args[PHILOSOPHERS]);
	philo_set_the_table(&spaghetti, args);
	philo_start_feeding(&spaghetti, args[PHILOSOPHERS]);

	return (0);
}
