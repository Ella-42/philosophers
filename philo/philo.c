/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:23:51 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/14 23:37:15 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//error handler
void	error(int type, t_pdata *pdata)
{
	if (type == ARGUMENT)
		printf("Error:\nInvalid argument(s)\nUsage: ./philo "
			"number_of_philosophers time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
	else if (type == MEM)
	{
		perror("Malloc");
		if (pdata->mtxa.mtx)
			free(pdata->mtxa.mtx);
		if (pdata->pta.pt)
			free(pdata->pta.pt);
		if (pdata)
			free(pdata);
	}
	exit(type);
}

//create threads, mutexes and run a simulation to test these
int	main(int ac, char **av)
{
	t_pdata	pdata;

	if (ac != 5 && ac != 6)
		error(ARGUMENT, NULL);
	arg2struct(ac, av, &pdata.args);
	mk_mutexes(&pdata.args, &pdata.mtxa, &pdata);
	mk_pthreads(&pdata.args, &pdata.pta, &pdata.mtxa, &pdata);
}
