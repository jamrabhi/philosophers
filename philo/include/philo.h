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
	pthread_t		thread_id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
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
	pthread_mutex_t	mutex;
	t_philo			*philo;
}				t_data;


int		exit_fail(char *str);
int		parsing(char *argv[], t_data *data);
long	timer(t_data *data);
void	ft_usleep(long time_ms);


int		ft_atoi(const char *str);
long	ft_atol(const char *str);

int		philo(t_data *data);

#endif
