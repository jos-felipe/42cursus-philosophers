/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/28 14:50:29 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_validate_user_inputs(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		printf("Args has been validated! %s\n", argv[0]);
	}
	else
	{
		write(STDERR_FILENO, "\nInvalid argument(s)\n", 21);
		printf(PHILO_ARGS);
		exit(EXIT_FAILURE);
	}
}
