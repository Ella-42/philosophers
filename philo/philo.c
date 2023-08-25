/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:23:51 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/25 17:56:00 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//error handler
void	error(int type)
{
	if (type == ARGUMENT)
		printf("Error:\nInvalid argument(s)\nUsage: ./philo "
			"number_of_philosophers time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
	exit(type);
}

//create threads, mutexes and run a simulation to test these
int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
		error(ARGUMENT);
	arg2struct(ac, av, &main.args);
	mk_mutexes(&main.args, &main.mtxa);
	mk_pthreads(&main.args, &main.pta, &main);
}
