/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:41:16 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/06/10 12:41:18 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_alive(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->data->check_alive_lock);
	time_since_last_meal = get_time() - philo->last_time_ate;
	if (time_since_last_meal > philo->data->time_die
		|| philo->data->dead_body == 1
		|| philo->nb_meals == philo->data->must_eat)
	{
		if (philo->data->dead_body == 0
			&& philo->nb_meals != philo->data->must_eat)
		{
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%ld %d died\n", timer(philo), philo->id);
			pthread_mutex_unlock(&philo->data->print_lock);
		}
		philo->data->dead_body = 1;
		pthread_mutex_unlock(&philo->data->check_alive_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->data->check_alive_lock);
	return (EXIT_SUCCESS);
}
