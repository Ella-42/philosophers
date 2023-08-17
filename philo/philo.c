/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:23:51 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/17 22:40:01 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//very basic string to number conversion
int	micro_atoi(char *str)
{
	int	nb;

	nb = 0;
	while (*str != '\0')
		nb = nb * 10 + (*str++ - 48);
	return (nb);
}

//error handler
void	error(int type)
{
	if (type == ARGUMENT)
		printf("Error:\nInvalid amount of arguments\n");
	exit(type);
}

//create threads, mutexes and run a simulation to test these
int	main(int ac, char **av)
{
	int	p_nb;

	if (5 > ac || ac > 6)
		error(ARGUMENT);
	p_nb = micro_atoi(av[1]);
	printf("%i philosophers\n", p_nb);
}
