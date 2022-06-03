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

long	timer(t_data *data)
{
	struct timeval	end_timer;
	long			time;

	gettimeofday(&end_timer, NULL);
	time = 0;
	time = (end_timer.tv_sec - data->timer_start.tv_sec) * 1000;
	time += (end_timer.tv_usec - data->timer_start.tv_usec) / 1000;
	return (time);
}
