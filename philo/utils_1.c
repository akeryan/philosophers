/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:26:13 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/20 15:05:59 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->thread_id[0], NULL, &routine, &data->philos[0]))
		return (error_msg("thread creation failed in one_philo()", data));
	pthread_detach(data->thread_id[0]);
	while (data->dead == false)
		usleep(10);
	destroy(data);
	return (0);
}

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
		pthread_mutex_destroy(&data->forks[i]);
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

//int	alert_sleeping(LONG sleep_time)
//{
	//while (get_time() < sleep_time)
	//{
		//usleep(100);
		//if (get_time() >= philo->time_to_die)
			//change_state(DIED, philo);
	//}

//}