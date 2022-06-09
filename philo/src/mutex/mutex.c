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

void	print_msg(long ms, int philo_id, char *str, t_data *data)
{
	pthread_mutex_lock(&data->msg);
	pthread_mutex_lock(&data->dead_m);
	if (!data->dead || (data->dead && !ft_strcmp(str, "died") && data->dead == 1))
		printf("%ld %d %s\n", ms, philo_id, str);
	pthread_mutex_unlock(&data->dead_m);
	pthread_mutex_unlock(&data->msg);
}

void	*check_death(void *mystruct)
{
	t_philo	*philo;

	philo = (t_philo *)mystruct;
	(void)philo;
	// printf("atec = %ld\n", philo->ate);
	// printf("get_time = %ld\n", get_time());
	if (get_time() - philo->time_ate > philo->data->time_die)
	{
		print_msg(timer(philo->data), philo->id, "died", philo->data);
		philo->data->dead++;
	}
	return (NULL);
}

int		is_dead(t_philo *philo)
{
	if ((get_time() - philo->time_ate) >= philo->data->time_die)
	{
		philo->data->dead++;
		print_msg(timer(philo->data), philo->id, "died", philo->data);
		return (1);
	}
	return (0);
}

void	*routine(void *mystruct)
{
	t_philo *philo;

	philo = (t_philo *)mystruct;
		// printf("nb time must eat = %d\nnb ate = %d\n", philo->data->nb_times_must_eat, philo->nb_ate);
	while (!is_dead(philo) && !philo->data->dead)
	{
		// pthread_create(&philo->check_death, NULL, &check_death, philo);
		pthread_mutex_lock(&philo->left_fork);
		print_msg(timer(philo->data), philo->id, "has taken a fork", philo->data);
		pthread_mutex_lock(philo->right_fork);
		print_msg(timer(philo->data), philo->id, "has taken a fork", philo->data);
		print_msg(timer(philo->data), philo->id, "is eating", philo->data);
		philo->nb_ate++;
		usleep(philo->data->time_eat * 1000);
		philo->time_ate = get_time();
		
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (philo->data->nb_times_must_eat > 0 && philo->nb_ate == philo->data->nb_times_must_eat)
			break;
		// usleep(5 *1000);
		pthread_mutex_lock(&philo->data->dead_m);
		if (!philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_m);
			print_msg(timer(philo->data), philo->id, "is sleeping", philo->data);
			usleep(philo->data->time_sleep * 1000);
			print_msg(timer(philo->data), philo->id, "is thinking", philo->data);
		}
		pthread_mutex_unlock(&philo->data->dead_m);
	}

	return (NULL);
}

int		philo(t_data *data)
{
	int	i;

	i = 0;
    gettimeofday(&data->timer_start, NULL);
	pthread_mutex_init(&data->msg, NULL);
	pthread_mutex_init(&data->dead_m, NULL);

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
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
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
		// printf("%ld %d is thinking\n", timer(data), i + 1);
		// printf("thread[%d] = %ld\n", data->philo[i].id, data->philo[i].thread_id);
		i++;
	}
	printf("time : %ld ms.\n", timer(data));
	return (EXIT_SUCCESS);
}
