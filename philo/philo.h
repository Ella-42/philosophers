/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:25:21 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/18 19:42:04 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*libraries*/

//exit
# include <stdlib.h>

//printf
# include <stdio.h>

//error codes (simulating errno)
# define ARGUMENT 22

//argument data structure
typedef struct s_arguments
{
	int	p_nb;
	int	f_nb;
	int	t2d;
	int	t2e;
	int	t2s;
	int	loop_nb;
}		t_arguments;

/**********************/
/*       philo        */
/**********************/

//error handler
void	error(int type);

//create threads, mutexes and run a simulation to test these
int		main(int ac, char **av);

/**********************/
/*        init        */
/**********************/

//very basic string to number conversion
int		micro_atoi(char *str);

//convert arguments into integer values and assign them to a structure
void	arg2struct(char **av, t_arguments *args, int ac);

#endif
