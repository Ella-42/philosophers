/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:25:21 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/25 19:41:57 by lpeeters         ###   ########.fr       */
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
	int			id;
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

//philisopher data
typedef struct s_pdata
{
	int		id;
	t_main	main;
}			t_pdata;

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
void	arg2struct(int ac, char **av, t_arguments *args);

//initialize mutexes
void	mk_mutexes(t_arguments *args, t_mutex_array *mtxa);

//initialize pthreads
void	mk_pthreads(t_arguments *args, t_pthread_array *pta, t_main *main);

/**********************/
/*       logic        */
/**********************/

//philisopher's behavior
void	*routine(void *p_id_ptr);

#endif
