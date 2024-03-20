/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:44:11 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/20 16:25:49 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	while (philo->data->dead == false)
	{
		pthread_mutex_lock(&philo->lock_1);
		if (philo->data->philos_done_eating >= philo->data->philo_num)
			philo->data->dead = true;
		pthread_mutex_unlock(&philo->lock_1);
	}
	return ((void *)0);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = get_time() + philo->data->life_span;
	while (philo->data->dead == false)
	{
		eat(philo);
		if (get_time() >= philo->time_to_die)
			change_state(DIED, philo);
		change_state(THINKING, philo);
	}
	return ((void *)0);
}

int	run(t_data *data)
{
	pthread_t	thd;
	int			i;

	i = -1;
	data->start_time = get_time();
	if (data->meals_num > 0)
	{
		if (pthread_create(&thd, NULL, &monitor, &data->philos[0]))
			return (error_msg("thread creation failed in run()", data));
	}
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->thread_id[i], NULL, &routine, &data->philos[i]))
			return (error_msg("thread creation failed in run()", data));
		usleep(100);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->thread_id[i], NULL))
			return (error_msg("pthread_join failed in run()", data));
	}
	return (0);
}