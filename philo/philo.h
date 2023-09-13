/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:25:21 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/13 15:42:29 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*libraries*/

//exit, malloc, free
# include <stdlib.h>

//printf, perror
# include <stdio.h>

//pthread_create
# include <pthread.h>

//error codes (simulating errno)
# define ARGUMENT 22
# define MEM 12

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

//philisopher data
typedef struct s_pdata
{
	int				id;
	t_arguments		args;
	t_pthread_array	pta;
	t_mutex_array	mtxa;
}					t_pdata;

/**********************/
/*       philo        */
/**********************/

//error handler
void	error(int type, t_pdata *pdata);

//exit the program in a clean way
void	exiter(t_pdata *pdata);

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
void	mk_mutexes(t_arguments *args, t_mutex_array *mtxa, t_pdata *pdata);

//initialize pthreads
void	mk_pthreads(t_arguments *args, t_pthread_array *pta, t_pdata *pdata);

/**********************/
/*       logic        */
/**********************/

//philisopher's behavior
void	*routine(void *p_id_ptr);

#endif
