/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:29:51 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/10 16:53:16 akeryan          ###   ########.fr       */
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

# define LONG			unsigned long long
# define THINKING		"is thinking"
# define SLEEPING		"is sleeping"
# define EATING			"is eating"
# define TAKE_FORK		"has taken a fork"
# define DIED			"died"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				eat_count;
	bool			eating;
	LONG			time_to_die;
	pthread_t		th;
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				meals_num;
	bool			dead;
	int				philos_done_eating;
	int				philo_num;
	LONG			life_span;
	LONG			eat_span;
	LONG			sleep_span;
	LONG			start_time;
	pthread_t		*thread_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

//	prime -------------------------------------------------------
int			run(t_data *data);
void		*routine(void *philo_ptr);
int			one_philo(t_data *data);

//	preprocessing --------------------------------------------------------
int			parsing(int argc, char *argv[]);
int			init(int argc, char **argv, t_data *data);

//	actions -----------------------------------------------------
void		eat(t_philo *philo);
int			grab_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

//	utils --------------------------------------------------------
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		free_data(t_data	*data);
void		destroy(t_data *data);
LONG		get_time(void);

// error handling/messaging --------------------------------------
int			error_msg(char *str, t_data *data);
void		change_state(char *str, t_philo *philo);

#endif