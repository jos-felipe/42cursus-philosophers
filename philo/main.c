/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/16 18:30:11 by josfelip         ###   ########.fr       */
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
	t_buffet			spaghetti;
	unsigned int		args[N_ARGS];

	philo_startup(args);
	philo_validate_argc(argc);
	philo_validate_argv(argc, argv);
	philo_assignment_args(argc, argv, args);
	assert(!philo_fill_the_list_of_diners(&spaghetti, args));
	philo_buffet_preparation(&spaghetti);
	philo_buffet_set_the_table(&spaghetti, args);
	philo_buffet_closing(&spaghetti);
	return (0);
}
