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

int	eat_philo(t_philo *philo, t_data *data)
{
	lock_forks(philo);
	if (check_alive(philo, data) == EXIT_SUCCESS)
	{
		sem_wait(philo->data->print_lock);
		printf("%ld %d is eating\n", timer(philo), philo->id);
		sem_post(philo->data->print_lock);
		philo->last_time_ate = get_time();
		ft_usleep(philo->data->time_eat);
		philo->nb_meals++;
		unlock_forks(philo);
		return (EXIT_SUCCESS);
	}
	else
	{
		unlock_forks(philo);
		return (EXIT_FAILURE);
	}
}

int	sleep_philo(t_philo *philo, t_data *data)
{
	int		sleep_time;

	sleep_time = philo->data->time_sleep;
	if (check_alive(philo, data) == EXIT_SUCCESS)
	{
		sem_wait(philo->data->print_lock);
		printf("%ld %d is sleeping\n", timer(philo), philo->id);
		sem_post(philo->data->print_lock);
		if (philo->data->time_eat * 2 >= philo->data->time_die
			|| philo->data->time_eat + philo->data->time_sleep
			>= philo->data->time_die)
			sleep_time = (philo->data->time_die - philo->data->time_eat + 1);
		ft_usleep(sleep_time);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

int	think_philo(t_philo *philo, t_data *data)
{
	if (check_alive(philo, data) == EXIT_SUCCESS)
	{
		sem_wait(philo->data->print_lock);
		printf("%ld %d is thinking\n", timer(philo), philo->id);
		sem_post(philo->data->print_lock);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
