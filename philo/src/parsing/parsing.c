/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:53:07 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/05/25 22:53:10 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_int_max(char *argv[])
{
	long	nb;
	int		i;

	i = 1;
	while (argv[i])
	{
		nb = ft_atol(argv[i]);
		if (nb > INT_MAX)
			return(EXIT_FAILURE);
		i++;
	}
	return(EXIT_SUCCESS);
}

int	args_are_digit(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parsing(char *argv[])
{
	if (args_are_digit(argv) == EXIT_FAILURE || check_int_max(argv) == 
		EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
