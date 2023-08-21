/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:25:21 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/21 18:43:17 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*libraries*/

//exit, malloc, free
# include <stdlib.h>

//printf
# include <stdio.h>

//pthread_create
# include <pthread.h>

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

//individual phtread data with their ID
typedef struct s_pthread
{
	pthread_t	thread;
}				t_pthread;

//data array of pthreads
typedef struct s_pthread_array
{
	t_pthread	*pt;
}				t_pthread_array;

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

void	mk_pthreads(t_arguments *args, t_pthread_array *pta);

#endif
