/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:23:51 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/18 21:43:51 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//error handler
void	error(int type)
{
	if (type == ARGUMENT)
		printf("Error:\nInvalid argument(s)\n");
	exit(type);
}

//create threads, mutexes and run a simulation to test these
int	main(int ac, char **av)
{
	t_arguments	args;

	if (5 > ac || ac > 6)
		error(ARGUMENT);
	arg2struct(av, &args, ac);
	printf("philosophers: %i\n", args.p_nb);
	printf("time to die: %i\n", args.t2d);
	printf("time to eat: %i\n", args.t2e);
	printf("time to sleep: %i\n", args.t2s);
	if (args.loop_nb)
		printf("number of times each philosopher must eat: %i\n", args.loop_nb);
}
