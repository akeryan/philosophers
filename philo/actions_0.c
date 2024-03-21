/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:02:41 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/21 21:27:01 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		printf("%llu %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->write);
}

static	int	check_fork(t_fork *fork, t_philo *philo)
{
	bool	fork_state;

	while (1)
	{
		pthread_mutex_lock(&fork->lock);
		fork_state = fork->is_taken;
		pthread_mutex_unlock(&fork->lock);
		if (fork_state == false)
		{
			pthread_mutex_lock(&fork->lock);
			fork->is_taken = true;
			pthread_mutex_unlock(&fork->lock);
			return (0);
		}
		else
		{
			usleep(10);
			if (get_time() > philo->time_to_die)
			{
				change_state(DIED, philo);
				return (-1);
			}
		}
	}
	return (0);
}

int	grab_forks(t_philo *philo)
{
	if (check_fork(philo->right_fork, philo) < 0)
		return (-1);
	change_state(TAKE_FORK, philo);
	if (philo->data->philo_num == 1)
	{
		while (get_time() < philo->time_to_die)
			usleep(100);
		change_state(DIED, philo);
	}
	else
	{
		if (check_fork(philo->left_fork, philo) < 0)
			return (-1);
		change_state(TAKE_FORK, philo);
	}
	return (0);
}

static void	while_asleep(t_philo *philo, LONG wake_up_time)
{
	bool	state;

	while (get_time() < wake_up_time)
	{
		pthread_mutex_lock(&philo->data->write);
		state = philo->data->dead;
		pthread_mutex_unlock(&philo->data->write);
		if (state == false)
		{
			usleep(100);
			if (get_time() >= philo->time_to_die)
			{
				change_state(DIED, philo);
				break ;
			}
		}
		else
			break ;
	}
}

void	drop_forks(t_philo *philo)
{
	LONG	wake_up_time;

	pthread_mutex_lock(&philo->left_fork->lock);
	philo->left_fork->is_taken = false;
	pthread_mutex_unlock(&philo->left_fork->lock);
	pthread_mutex_lock(&philo->right_fork->lock);
	philo->right_fork->is_taken = false;
	pthread_mutex_unlock(&philo->right_fork->lock);
	change_state(SLEEPING, philo);
	wake_up_time = get_time() + philo->data->sleep_span;
	while_asleep(philo, wake_up_time);
}
