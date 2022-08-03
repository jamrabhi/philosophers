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

void	eat(t_philo *philo)
{
	if (philo->id == philo->data->nb_philo)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	if (check_alive(philo) == EXIT_SUCCESS)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d has taken a fork\n", timer(philo), philo->id);
		printf("%ld %d has taken a fork\n", timer(philo), philo->id);
		printf("%ld %d is eating\n", timer(philo), philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		philo->last_time_ate = get_time();
		usleep(philo->data->time_eat * 1000);
		philo->nb_meals++;
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*thread_routine(void *philo_struct)
{
	t_philo	*philo;

	philo = philo_struct;
	while (check_alive(philo) == EXIT_SUCCESS)
	{
		eat(philo);
		if (check_alive(philo) == EXIT_SUCCESS)
		{
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%ld %d is thinking\n", timer(philo), philo->id);
			printf("%ld %d is sleeping\n", timer(philo), philo->id);
			usleep(philo->data->time_sleep);
			pthread_mutex_unlock(&philo->data->print_lock);
		}
	}
	return (NULL);
}

void	run_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, thread_routine,
			&data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	gettimeofday(&data->timer_start, NULL);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0
		|| pthread_mutex_init(&data->check_alive_lock, NULL) != 0)
		return (EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->philo[i].left_fork, NULL) != 0)
			return (EXIT_FAILURE);
		data->philo[i].right_fork = &data->philo[(i + 1) % data->nb_philo]
			.left_fork;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].last_time_ate = get_time();
		data->philo[i].nb_meals = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	philo(t_data *data)
{
	if (init_philo(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	run_philo(data);
	free(data->philo);
	return (EXIT_SUCCESS);
}
