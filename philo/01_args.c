/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/08/19 11:12:21 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_validate_argv(int argc, char *argv[])
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf(OUT_OF_BOUNDS_FATAL, i);
			printf(OUT_OF_BOUNDS_INFO, argv[i]);
			status = 1;
		}
	}
	return (status);
}

void	philo_assignment_args(int argc, char *argv[], int *args)
{
	int	i;

	i = 0;
	while (++i < argc)
		args[i - 1] = ft_atoi(argv[i]);
}
