/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:21:14 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/05/31 21:21:18 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(void *mystruct)
{
	t_philo *philo;

	philo = (t_philo *)mystruct;
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	usleep(philo->data->time_eat * 1000);
	printf("philo [%d] eat\n", philo->id);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	// printf("mutex = %p\n", &philo->data->mutex);
	// pthread_mutex_unlock(&philo->data->mutex);
	// printf("test from thread[%d] %ld unlocked\n", philo->id, philo->thread_id);
	return (NULL);
}

int		philo(t_data *data)
{
	int	i;

	i = 0;
    gettimeofday(&data->timer_start, NULL);
	// if (pthread_mutex_init(&data->mutex, NULL) != 0)
	// 	return (EXIT_FAILURE);
	// printf("mutex = %p\n", &data->mutex);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (i == data->nb_philo - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (i % 2 == 1)
			usleep(data->time_eat * 1000);
		if (pthread_create(&data->philo[i].thread_id, NULL, &routine, &data->philo[i]) != 0)
			return(EXIT_FAILURE);
		// printf("thread[%d] = %ld\n", data->philo[i].id, data->philo[i].thread_id);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return(EXIT_FAILURE);
		// printf("thread[%d] = %ld\n", data->philo[i].id, data->philo[i].thread_id);
		i++;
	}
	if (pthread_mutex_destroy(&data->mutex) != 0)
		return (EXIT_FAILURE);
	printf("time : %ld ms.\n", timer(data));
	return (EXIT_SUCCESS);
}
