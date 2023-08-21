/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:23:51 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/21 18:25:22 by lpeeters         ###   ########.fr       */
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
	t_arguments		args;
	t_pthread_array	pta;

	if (5 > ac || ac > 6)
		error(ARGUMENT);
	arg2struct(av, &args, ac);
	mk_pthreads(&args, &pta);
	printf("philosophers: %i\n", args.p_nb);
	printf("time to die: %i\n", args.t2d);
	printf("time to eat: %i\n", args.t2e);
	printf("time to sleep: %i\n", args.t2s);
	if (args.loop_nb)
		printf("number of times each philosopher must eat: %i\n", args.loop_nb);
}
