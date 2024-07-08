/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/08 11:34:06 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_validate_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf(PHILO_FATAL_ERROR);
		printf(PHILO_ARGS);
		exit(EXIT_FAILURE);
	}
}

void	philo_validate_argv(int argc, char *argv[], \
t_philo *philo)
{
	unsigned int	candidate;
	int				i;

	i = 1;
	while (i < argc)
	{
		candidate = ft_atou(argv[i]);
		if (candidate > 0)
			philo->args[i - 1] = candidate;
		else
		{
			printf(OUT_OF_BOUNDS_FATAL, i);
			printf(OUT_OF_BOUNDS_INFO, argv[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	philo_validate_argv_(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_atou(argv[i]) <= 0)
		{
			printf(OUT_OF_BOUNDS_FATAL, i);
			printf(OUT_OF_BOUNDS_INFO, argv[i]);
			exit(EXIT_FAILURE);
		}
	}
}
