/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/08 14:54:52 by josfelip         ###   ########.fr       */
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
	t_philo			data;
	unsigned int	args[N_ARGS];

	philo_startup(args);
	philo_validate_argc(argc);
	philo_validate_argv(argc, argv);
	philo_assignment_args(argc, argv, args);
	philo_allocation(&data, args);
	philo_dallocation(&data, args[PHILOSOPHERS]);
	printf("Main program has ended.\n");
	return (0);
}
