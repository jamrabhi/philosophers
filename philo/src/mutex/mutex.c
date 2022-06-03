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

    struct timeval t1, t2;
    double elapsedTime = 0;

    // start timer
    gettimeofday(&t1, NULL);

    // do something
    usleep(100);



	i = 0;

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("%f ms.\n", elapsedTime);

	pthread_mutex_init(&data->mutex, NULL);
	printf("mutex = %p\n", &data->mutex);
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
	pthread_mutex_destroy(&data->mutex);
	return (EXIT_SUCCESS);
}

