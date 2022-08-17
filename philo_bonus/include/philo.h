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
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long			last_time_ate;
	struct s_data	*data;
	pid_t			process;
	int				wait_status;

}				t_philo;

typedef struct s_data
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		must_eat;
	int		dead_body;
	long	timer_start;
	sem_t	*print_lock;
	sem_t	*check_alive_lock;
	sem_t	*fork;
	sem_t	*take_forks;
	t_philo	*philo;
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

int		eat_philo(t_philo *philo);
int		sleep_philo(t_philo *philo);
int		think_philo(t_philo *philo);

void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
// int		destroy_mutex(t_data *data);

#endif
