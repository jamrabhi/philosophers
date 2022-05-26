/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 04:04:39 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/05/22 04:04:42 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_times_must_eat;
}				t_data;

int		parsing(char *argv[], t_data *data);
int		exit_fail(char *str);

int		ft_atoi(const char *str);
long	ft_atol(const char *str);

#endif
