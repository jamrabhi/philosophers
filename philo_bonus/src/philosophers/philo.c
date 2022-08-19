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

// void	*routine_philo(void *philo_struct)
// {
// 	t_philo	*philo;

// 	philo = philo_struct;
// 	if (philo->id % 2 == 0)
// 		ft_usleep(philo->data->time_eat);
// 	while (check_alive(philo) == EXIT_SUCCESS)
// 	{
// 		eat_philo(philo);
// 		sleep_philo(philo);
// 		think_philo(philo);
// 	}
// 	return (NULL);
// }

void	run_philo(t_philo *philo)
{
	while (check_alive(philo) == EXIT_SUCCESS)
	{
		if (eat_philo(philo) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (sleep_philo(philo) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (think_philo(philo) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	init_philo(t_data *data)
{
	int	i;
	int	status_pid;

	i = 0;
	sem_unlink("/print_lock");
	sem_unlink("/check_alive_lock");
	sem_unlink("/fork");
	sem_unlink("/take_forks");
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (EXIT_FAILURE);
	data->timer_start = get_time();
	data->print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
	data->check_alive_lock = sem_open("/check_alive_lock", O_CREAT, 0644, 1);
	data->fork = sem_open("/fork", O_CREAT, 0644, data->nb_philo);
	data->take_forks = sem_open("/take_forks", O_CREAT, 0644, 2);
	if (data->print_lock == SEM_FAILED || data->check_alive_lock == SEM_FAILED
		|| data->fork == SEM_FAILED || data->take_forks == SEM_FAILED)
		return (EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].last_time_ate = get_time();
		data->philo[i].nb_meals = 0;
		data->philo[i].process = fork();
		if (data->philo[i].process == -1)
			return (EXIT_FAILURE);
		if (data->philo[i].process == 0)
			run_philo(&data->philo[i]);
		i++;
	}
	i = 0;
	// while (i < data->nb_philo)
	// {
	// 	i++;
	// }
	waitpid(-1, &status_pid, 0);
	if (WIFEXITED(status_pid))
	{
		while (i < data->nb_philo)
		{
			kill(data->philo[i].process, SIGTERM);
			i++;
		}
		if (sem_unlink("/print_lock") != 0 || sem_unlink("/check_alive_lock") != 0
			|| sem_unlink("/fork") != 0 || sem_unlink("take_forks") != 0)
			return (EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}

int	philo(t_data *data)
{
	if (init_philo(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// if (run_philo(data) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	// if (destroy_mutex(data) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	free(data->philo);
	return (EXIT_SUCCESS);
}
