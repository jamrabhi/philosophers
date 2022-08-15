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

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
}

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
}

int	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->print_lock) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&data->check_alive_lock) != 0)
		return (EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&data->philo[i].left_fork) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
