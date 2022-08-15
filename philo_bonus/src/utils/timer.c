/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:09:52 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/06/04 00:09:58 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	get_time(void)
{
	struct timeval	start_time;
	long			rt;

	gettimeofday(&start_time, NULL);
	rt = (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	return (rt);
}

long	timer(t_philo *philo)
{
	return (get_time() - philo->data->timer_start);
}

void	ft_usleep(long time_ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_ms)
		usleep(10);
}
