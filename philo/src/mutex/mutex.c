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
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print_msg(timer(philo), philo->id, "has taken a fork", philo);
	print_msg(timer(philo), philo->id, "has taken a fork", philo);
	print_msg(timer(philo), philo->id, "is eating", philo);
	philo->nb_ate++;
	philo->time_ate = get_time();
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *mystruct)
{
	t_philo	*philo;

	philo = (t_philo *)mystruct;
	philo->time_start = get_time();
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_eat);
	while (!philo->stop)
	{
		if (philo->nb_ate == philo->nb_times_must_eat || philo->stop)
			return (NULL);
		eat(philo);
		if (philo->nb_ate == philo->nb_times_must_eat || philo->stop)
			return (NULL);
		print_msg(timer(philo), philo->id, "is sleeping", philo);
		ft_usleep(philo->time_sleep);
		if (philo->nb_ate == philo->nb_times_must_eat || philo->stop)
			return (NULL);
		print_msg(timer(philo), philo->id, "is thinking", philo);
	}
	return (NULL);
}

void	*monitor(void *mystruct)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)mystruct;
	while (data->philo[i].stop == 0)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (data->philo[i].nb_ate == data->philo[i].nb_times_must_eat
				|| data->philo[i].stop)
				return (NULL);
			if (get_time() - data->philo[i].time_ate > data->philo[i].time_die)
			{
				philo_dead(data, &data->philo[i]);
				pthread_mutex_unlock(&data->philo[i].msg);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	init_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (i == data->nb_philo - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].time_ate = get_time();
		data->philo[i].nb_ate = 0;
		data->philo[i].stop = 0;
		data->philo[i].timer_start = data->timer_start;
		data->philo[i].nb_times_must_eat = data->nb_times_must_eat;
		data->philo[i].time_eat = data->time_eat;
		data->philo[i].time_sleep = data->time_sleep;
		data->philo[i].time_die = data->time_die;
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		pthread_mutex_init(&data->philo[i].msg, NULL);
		i++;
	}
}

int	philo(t_data *data)
{
	int	i;

	i = 0;
	gettimeofday(&data->timer_start, NULL);
	init_thread(data);
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, &routine,
				&data->philo[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	pthread_create(&data->monitor_th, NULL, &monitor, data);
	pthread_join(data->monitor_th, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	destroy_mutex(data);
	return (EXIT_SUCCESS);
}
