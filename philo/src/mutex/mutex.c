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
	t_data *data;

	data = (t_data *)mystruct;
	pthread_mutex_lock(&data->mutex);
	printf("test from thread\n");
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

int		philo(t_data *data)
{
	int	i;
	pthread_t thread[data->nb_philo];

	i = 0;
    gettimeofday(&data->timer_start, NULL);
	usleep(100 * 10);
	printf("time : %ld ms.\n", timer(data));
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		return (EXIT_FAILURE);
	// printf("mutex = %p\n", &data->mutex);
	while (i < data->nb_philo)
	{
		if (pthread_create(&thread[i], NULL, &routine, data) != 0)
			return(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return(EXIT_FAILURE);
		i++;
	}
	if (pthread_mutex_destroy(&data->mutex) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

