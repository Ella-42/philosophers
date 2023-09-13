/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:23:51 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/13 15:23:10 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//error handler
void	error(int type, t_main *main, t_pdata *pdata)
{
	if (type == ARGUMENT)
		printf("Error:\nInvalid argument(s)\nUsage: ./philo "
			"number_of_philosophers time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
	else if (type == MEM)
	{
		perror("Malloc");
		if (main->mtxa.mtx)
			free(main->mtxa.mtx);
		if (main->pta.pt)
			free(main->pta.pt);
		if (pdata)
			free(pdata);
	}
	exit(type);
}

//exit the program in a clean way
void	exiter(t_main *main)
{
	if (main->mtxa.mtx)
		free(main->mtxa.mtx);
	if (main->pta.pt)
		free(main->pta.pt);
	exit(EXIT_SUCCESS);
}

//create threads, mutexes and run a simulation to test these
int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
		error(ARGUMENT, NULL, NULL);
	arg2struct(ac, av, &main.args);
	mk_mutexes(&main.args, &main.mtxa, &main);
	mk_pthreads(&main.args, &main.pta, &main);
	exiter(&main);
}
