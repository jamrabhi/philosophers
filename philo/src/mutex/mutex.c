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

void	*check_death(void *mystruct)
{
	t_philo	*philo;

	philo = (t_philo *)mystruct;
	(void)philo;
	printf("atec = %ld\n", philo->ate);
	printf("get_time = %ld\n", get_time());
	if (get_time() - philo->ate > philo->data->time_die)
		printf("%ld %d died\n", timer(philo->data), philo->id);
	return (NULL);
}

void	*routine(void *mystruct)
{
	t_philo *philo;

	philo = (t_philo *)mystruct;
	pthread_create(&philo->check_death, NULL, &check_death, philo);
	pthread_mutex_lock(&philo->left_fork);
	printf("%ld %d has taken a fork\n", timer(philo->data), philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n", timer(philo->data), philo->id);
	printf("%ld %d is eating\n", timer(philo->data), philo->id);
	usleep(philo->data->time_eat * 1000);
	philo->ate = get_time();
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printf("%ld %d is sleeping\n", timer(philo->data), philo->id);
	usleep(philo->data->time_sleep * 1000);
	printf("%ld %d is thinking\n", timer(philo->data), philo->id);

	return (NULL);
}

int		philo(t_data *data)
{
	int	i;

	i = 0;
    gettimeofday(&data->timer_start, NULL);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (i == data->nb_philo - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].ate = get_time();
		printf("ateeee = %ld\n", data->philo[i].ate);
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
		printf("%ld %d is thinking\n", timer(data), i + 1);
		// printf("thread[%d] = %ld\n", data->philo[i].id, data->philo[i].thread_id);
		i++;
	}
	printf("time : %ld ms.\n", timer(data));
	return (EXIT_SUCCESS);
}
