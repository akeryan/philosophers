/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:02:41 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/10 17:38:35 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

LONG	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_msg("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (LONG)1000) + (tv.tv_usec / 1000));
}

void	print_state(char *str, t_philo *philo)
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
	pthread_mutex_lock(philo->r_fork);
	print_state(FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	print_state(FORK, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_state(SLEEPING, philo);
	ft_usleep(philo->data->sleep_span);
}

void	eat(t_philo *philo)
{
	grab_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->life_span;
	print_state(EATING, philo);
	philo->eat_count++;
	ft_usleep(philo->data->eat_span);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
