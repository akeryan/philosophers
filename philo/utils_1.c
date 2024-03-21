/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:26:13 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/21 21:20:14 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data	*data)
{
	if (data->thread_id)
		free(data->thread_id);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	destroy(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i].lock);
		pthread_mutex_destroy(&data->philos[i].lock_1);
		pthread_mutex_destroy(&data->philos[i].lock_2);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	free_data(data);
}

int	error_msg(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		destroy(data);
	return (1);
}

LONG	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_msg("gettimeofday() failed in get_time()\n", NULL));
	return ((tv.tv_sec * (LONG)1000) + (tv.tv_usec / 1000));
}
