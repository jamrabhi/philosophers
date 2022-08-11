/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 01:41:57 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/08/11 01:42:00 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine_philo(void *philo_struct)
{
	t_philo	*philo;

	philo = philo_struct;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_eat);
	while (check_alive(philo) == EXIT_SUCCESS)
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}

void	run_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, routine_philo,
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
	destroy_mutex(data);
	free(data->philo);
	return (EXIT_SUCCESS);
}
