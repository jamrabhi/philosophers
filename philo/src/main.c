/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 04:09:45 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/05/22 04:09:55 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (argc != 5 && argc != 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (parsing(argv, &data) == EXIT_FAILURE)
		return(exit_fail("Error : Arguments are not formatted correctly"));
	data.philo = malloc(sizeof(t_philo) * data.nb_philo);
	printf("DATA :\ndata.nb_philo = %d\ndata.time_die = %d\n", data.nb_philo,
		data.time_die);
	printf("data.time_eat = %d\ndata.time_sleep = %d\ndata.must_eat = %d\n-------\n", data.time_eat,
		data.time_sleep, data.nb_times_must_eat);
	if (philo(&data) == EXIT_FAILURE)
		return (exit_fail("Error : Mutex failed"));
	free(data.philo);
	return (0);
}
