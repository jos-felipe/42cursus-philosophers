/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/07/03 11:37:05 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	philo_validate_user_inputs(int argc, char *argv[])
// {
// 	if (argc == 5 || argc == 6)
// 	{
// 		printf("Args has been validated! %s\n", argv[0]);
// 	}
// 	else
// 	{
// 		printf(PHILO_FATAL_ERROR);
// 		printf(PHILO_ARGS);
// 		exit(EXIT_FAILURE);
// 	}
// }

void	philo_validate_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf(PHILO_FATAL_ERROR);
		printf(PHILO_ARGS);
		exit(EXIT_FAILURE);
	}
}
