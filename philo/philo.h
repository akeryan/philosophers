/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:29:51 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/10 14:44:04 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_FORKS		"has taken a fork"
# define THINKING		"is thinking"
# define SLEEPING		"is sleeping"
# define EATING			"is eating"
# define DIED			"died"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*thread_id;
	int				meals_num;
	int				dead;
	int				finished;
	t_philo			*philos;
	int				philo_num;
	u_int64_t		life_span;
	u_int64_t		eat_span;
	u_int64_t		sleep_span;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

//	utils_0
int			parsing(int argc, char *argv[]);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		messages(char *str, t_philo *philo);

//	utils_1
int			one_philo(t_data *data);
void		free_data(t_data	*data);
void		destroy(t_data *data);
int			error_msg(char *str, t_data *data);

//	time
u_int64_t	get_time(void);
int			ft_usleep(useconds_t time);

//	init
int			init(int argc, char **argv, t_data *data);
int			run(t_data *data);

//	actions
void		eat(t_philo *philo);

//	threads
void		*routine(void *philo_pointer);
#endif