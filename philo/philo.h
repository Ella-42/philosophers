/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:25:21 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/24 14:47:12 by lpeeters         ###   ########.fr       */
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

//data array of pthreads
typedef struct s_pthread_array
{
	pthread_t	*pt;
}				t_pthread_array;

//data array of mutexes
typedef struct s_mutex_array
{
	pthread_mutex_t	*mtx;
}					t_mutex_array;

//main struct within which all data is stored
typedef struct s_main
{
	t_arguments		args;
	t_pthread_array	pta;
	t_mutex_array	mtxa;
}					t_main;

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

//initialize pthreads
void	mk_pthreads(t_arguments *args, t_pthread_array *pta);

//initialize mutexes
void	mk_mutexes(t_arguments *args, t_mutex_array *mtxa);

/**********************/
/*       logic        */
/**********************/

//silence the errors
void	*anti_error(void *arg);

#endif
