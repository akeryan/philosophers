/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:02:41 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/12 13:25:26 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

LONG	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_msg("gettimeofday() failed in get_time()\n", NULL));
	return ((tv.tv_sec * (LONG)1000) + (tv.tv_usec / 1000));
}

void	change_state(char *str, t_philo *philo)
{
	LONG	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == false)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = true;
	}
	if (philo->data->dead == false)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	change_state(FORK, philo);
	if (philo->data->philo_num > 1)
		pthread_mutex_lock(philo->left_fork);
	else
	{
		while (get_time() < philo->time_to_die)
			usleep(100);
		change_state(DIED, philo);
	}
	change_state(FORK, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	change_state(SLEEPING, philo);
	usleep(philo->data->sleep_span * 1000);
}

static void	*concious_sleep(t_philo *philo, unsigned long eating_span)
{
	while (get_time() < eating_span)
	{
		usleep(100);
		if (get_time() >= philo->time_to_die)
			change_state(DIED, philo);
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
	return ((void *)0);
}

void	eat(t_philo *philo)
{
	grab_forks(philo);
	pthread_mutex_lock(&philo->lock_1);
	philo->eating = true;
	philo->time_to_die = get_time() + philo->data->life_span;
	change_state(EATING, philo);
	concious_sleep(philo, get_time() + philo->data->eat_span);
	philo->eating = false;
	pthread_mutex_unlock(&philo->lock_1);
	drop_forks(philo);
}
