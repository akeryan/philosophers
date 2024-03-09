/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:06:06 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/09 10:38:36 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	parsing(int argc, char *argv[], int *args)
{
	int		candidate;
	int		i;
	
	if (argc < 5 || argc > 6)
	{
		printf ("Wrong number of arguments\n");
		exit(1);
	}
	i = 0;	
	while (++i < argc)	
	{
		candidate = atoi(argv[i]);
		if (candidate <= 0)
		{
			printf("All the inputs must be positive integers\n");
			exit (1);
		}
		args[i - 1] = candidate;
	}
}