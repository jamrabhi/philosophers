/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 02:01:12 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/08/11 02:01:13 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_alive(t_philo *philo)
{
	long	time_since_last_meal;

	sem_wait(philo->data->check_alive_lock);
	time_since_last_meal = get_time() - philo->last_time_ate;
	if (time_since_last_meal > philo->data->time_die
		|| philo->data->dead_body == 1)
	{
		if (philo->data->dead_body == 0)
		{
			sem_wait(philo->data->print_lock);
			printf("%ld %d died\n", timer(philo), philo->id);
			sem_post(philo->data->print_lock);
		}
		philo->data->dead_body = 1;
		sem_post(philo->data->check_alive_lock);
		return (EXIT_FAILURE);
	}
	if (philo->nb_meals == philo->data->must_eat)
	{
		sem_post(philo->data->check_alive_lock);
		return (EXIT_FAILURE);
	}
	sem_post(philo->data->check_alive_lock);
	return (EXIT_SUCCESS);
}
