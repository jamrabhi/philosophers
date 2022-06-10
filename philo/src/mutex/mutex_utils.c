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

void	print_msg(long ms, int philo_id, char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->msg);
	printf("%ld %d %s\n", ms, philo_id, str);
	pthread_mutex_unlock(&philo->msg);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].left_fork);
		pthread_mutex_destroy(&data->philo[i].msg);
		i++;
	}
}

void	philo_dead(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->msg);
	printf("%ld %d died\n", get_time() - philo->time_start, philo->id);
	while (i < data->nb_philo)
	{
		data->philo[i].stop = 1;
		i++;
	}
}
