/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:25:39 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/21 21:26:49 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	concious_sleep(t_philo *philo, unsigned long eating_span)
{
	while (get_time() < eating_span)
	{
		usleep(100);
		if (get_time() >= philo->time_to_die)
		{
			change_state(DIED, philo);
			return (-1);
		}
	}
	pthread_mutex_lock(&philo->lock_2);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock_2);
	if (philo->eat_count == philo->data->meals_num)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->philos_done_eating++;
		pthread_mutex_unlock(&philo->data->lock);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	if (grab_forks(philo) < 0)
		return ;
	pthread_mutex_lock(&philo->lock_1);
	change_state(EATING, philo);
	philo->eating = true;
	concious_sleep(philo, get_time() + philo->data->eat_span);
	philo->time_to_die = get_time() + philo->data->life_span;
	philo->eating = false;
	pthread_mutex_unlock(&philo->lock_1);
	drop_forks(philo);
}
