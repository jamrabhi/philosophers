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
	sem_wait(philo->data->take_forks);
	sem_wait(philo->data->fork);
	sem_wait(philo->data->print_lock);
	printf("%ld %d has taken a fork\n", timer(philo), philo->id);
	sem_post(philo->data->print_lock);
	sem_wait(philo->data->fork);
	sem_wait(philo->data->print_lock);
	printf("%ld %d has taken a fork\n", timer(philo), philo->id);
	sem_post(philo->data->print_lock);
}

void	unlock_forks(t_philo *philo)
{
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	sem_post(philo->data->take_forks);
}

// int	destroy_mutex(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (pthread_mutex_destroy(&data->print_lock) != 0)
// 		return (EXIT_FAILURE);
// 	if (pthread_mutex_destroy(&data->check_alive_lock) != 0)
// 		return (EXIT_FAILURE);
// 	while (i < data->nb_philo)
// 	{
// 		if (pthread_mutex_destroy(&data->philo[i].left_fork) != 0)
// 			return (EXIT_FAILURE);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }
