/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 04:04:39 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/05/22 04:04:42 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_data	*data;
	long			last_time_ate;

}				t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				dead_body;
	struct timeval	timer_start;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	check_alive_lock;
	t_philo			*philo;
}				t_data;

int		parsing(char *argv[], t_data *data);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		exit_fail(char *str);

long	timer(t_philo *philo);
long	get_time(void);
void	ft_usleep(long time_ms);

int		philo(t_data *data);
void	case_one(t_data *data);

int		check_alive(t_philo *philo);

void	eat_philo(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think_philo(t_philo *philo);

void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
void	destroy_mutex(t_data *data);

#endif
