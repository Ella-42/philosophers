/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:23:51 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/16 22:48:28 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(int type)
{
	if (type == ARGUMENT)
		printf("Error:\nInvalid amount of arguments\n");
	exit(type);
}

int	main(int ac, char **av)
{
	(void)av;
	if (5 > ac || ac > 6)
		error(ARGUMENT);
	return (2147483392);
}
