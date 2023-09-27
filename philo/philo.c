/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:23:51 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/27 23:31:50 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//exit the program in a clean way
int	exiter(int type, t_pdata *pdata, t_pthread_array *pta, t_mutex_array *mtxa)
{
	if (type == ARGUMENT)
	{
		printf("Error:\nInvalid argument(s)\n");
		return (1);
	}
	if (type == MEM)
	{
		free(pdata->mtxa.mtx);
		free(pdata->args.time.start);
		free(pdata->args.time.end);
	}
	if (type == PDATA || type == ALL)
	{
		free(mtxa->mtx);
		free(mtxa->args.time.start);
		free(mtxa->args.time.end);
		free(pta->pt);
		if (pdata != NULL)
			free(pdata);
	}
	if (type == THREAD)
		free_data(pdata);
	if (type == ALL)
		return (0);
	return (1);
}

//create threads, mutexes and run a simulation to test these
int	main(int ac, char **av)
{
	t_pdata	pdata;

	if (ac != 5 && ac != 6)
		return (exiter(ARGUMENT, NULL, NULL, NULL));
	if (arg2struct(ac, av, &pdata.args))
		return (1);
	if (mk_mutexes(&pdata.args, &pdata.mtxa, &pdata))
		return (1);
	if (mk_pthreads(&pdata.args, &pdata.pta, &pdata.mtxa, &pdata))
		return (1);
	return (exiter(ALL, NULL, &pdata.pta, &pdata.mtxa));
}
