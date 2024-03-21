/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:06:06 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/21 21:33:35 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	parsing(int argc, char *argv[])
{
	int		i;
	int		value;

	if (argc < 5 || argc > 6)
	{
		printf ("Wrong number of arguments\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		value = atoi(argv[i]);
		if (value <= 0)
		{
			printf("All the inputs must be positive integers\n");
			return (1);
		}
	}
	return (0);
}
