/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:28:35 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/10 18:36:06 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_alloc(t_data *data)
{
	data->thread_id = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->thread_id)
		return (error_msg("malloc failed in init_alloc()_1", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (error_msg("malloc failed in init_alloc()_2", data));
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (error_msg("malloc failed in init_alloc()_3", data));
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->philo_num - 1];
	while (++i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->life_span;
		data->philos[i].eat_count = 0;
		data->philos[i].eating = false;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->philo_num = (int) ft_atoi(argv[1]);
	data->life_span = (LONG) ft_atoi(argv[2]);
	data->eat_span = (LONG) ft_atoi(argv[3]);
	data->sleep_span = (LONG) ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_num = (int) ft_atoi(argv[5]);
	else
		data->meals_num = -1;
	data->dead = false;
	data->philos_done_eating = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	init(int argc, char **argv, t_data *data)
{
	if (init_data(argc, argv, data))
		return (1);
	if (init_alloc(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_philos(data);
	return (0);
}
