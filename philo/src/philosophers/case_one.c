/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:12:03 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/06/10 12:12:07 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*myroutine(void *data_struct)
{
	t_data			*data;
	pthread_mutex_t	my_fork;

	data = data_struct;
	pthread_mutex_init(&my_fork, NULL);
	pthread_mutex_lock(&my_fork);
	printf("0 1 has taken a fork\n");
	ft_usleep(data->time_die);
	pthread_mutex_unlock(&my_fork);
	printf("%d 1 died\n", data->time_die);
	pthread_mutex_destroy(&my_fork);
	return (NULL);
}

void	case_one(t_data *data)
{
	pthread_t		thread;

	pthread_create(&thread, NULL, myroutine, data);
	pthread_join(thread, NULL);
}
