/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:52:10 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/21 21:12:29 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(argc, argv) == 1)
		return (1);
	if (init(argc, argv, &data) == 1)
		return (1);
	if (run(&data) == 1)
		return (1);
	destroy(&data);
	return (0);
}
