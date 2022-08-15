/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 01:46:11 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/08/11 01:46:13 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat_philo(t_philo *philo)
{
	lock_forks(philo);
	if (check_alive(philo) == EXIT_SUCCESS)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d has taken a fork\n", timer(philo), philo->id);
		printf("%ld %d has taken a fork\n", timer(philo), philo->id);
		printf("%ld %d is eating\n", timer(philo), philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		philo->last_time_ate = get_time();
		ft_usleep(philo->data->time_eat);
		philo->nb_meals++;
	}
	unlock_forks(philo);
}

void	sleep_philo(t_philo *philo)
{
	int		sleep_time;

	sleep_time = philo->data->time_sleep;
	if (check_alive(philo) == EXIT_SUCCESS)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d is sleeping\n", timer(philo), philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		if (philo->data->time_eat * 2 >= philo->data->time_die
			|| philo->data->time_eat + philo->data->time_sleep
			>= philo->data->time_die)
			sleep_time = (philo->data->time_die - philo->data->time_eat + 1);
		ft_usleep(sleep_time);
	}
}

void	think_philo(t_philo *philo)
{
	if (check_alive(philo) == EXIT_SUCCESS)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d is thinking\n", timer(philo), philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
}
