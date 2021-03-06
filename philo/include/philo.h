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
	long			time_ate;
	struct timeval	timer_start;
	int				nb_ate;
	int				stop;
	long			time_start;
	int				nb_times_must_eat;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	pthread_t		thread_id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	msg;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_times_must_eat;
	struct timeval	timer_start;
	pthread_t		monitor_th;
	t_philo			*philo;
}				t_data;

int		exit_fail(char *str);
int		parsing(char *argv[], t_data *data);
long	timer(t_philo *philo);
void	ft_usleep(long time_ms);
long	get_time(void);
int		ft_strcmp(const char *s1, const char *s2);
void	case_one(t_data *data);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		philo(t_data *data);
void	print_msg(long ms, int philo_id, char *str, t_philo *philo);
void	destroy_mutex(t_data *data);
void	philo_dead(t_data *data, t_philo *philo);

#endif
