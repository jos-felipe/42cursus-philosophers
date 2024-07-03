/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/03 13:49:31 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo)
{
	int	i;
	
	i = -1;
	while (++i < N_ARGS)
		philo->args[i] = 0;
}

void	philo_debug(t_philo	*philo)
{	
	int	i;
	
	i = -1;
	while (++i < N_ARGS)
		printf("philo->args[%d] = %u\n", i, philo->args[i]);
	
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	
	philo_init(&philo);
	philo_debug(&philo);
	philo_validate_argc(argc);
	// philo_validate_argv(argc, argv, &philo);
	printf("name: %s", argv[0]);
	return (0);
}
