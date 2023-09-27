/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:25:21 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/27 23:06:18 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*libraries*/

//malloc, free
# include <stdlib.h>

//printf
# include <stdio.h>

//pthread functions
# include <pthread.h>

//usleep
# include <unistd.h>

//gettimeofday
# include <sys/time.h>

/*macros*/

//error codes (simulating errno)
# define ARGUMENT 22
# define MEM 12
# define THREAD -12
# define PDATA 1212
# define ALL 0

//status indicators
# define THINKING 0
# define HUNGRY 0
# define RUNNING 0
# define EATING 1
# define FULL 1
# define END 1
# define SLEEPING 2
# define DEAD -1

/*data structures*/

//time struct
typedef struct s_time
{
	struct timeval	*start;
	struct timeval	*end;
}					t_time;

//argument data structure
typedef struct s_arguments
{
	int		p_nb;
	int		f_nb;
	int		t2d;
	int		t2e;
	int		t2s;
	int		loop_nb;
	t_time	time;
}			t_arguments;

//data array of pthreads
typedef struct s_pthread_array
{
	pthread_t	*pt;
}				t_pthread_array;

//data array of mutexes
typedef struct s_mutex_array
{
	t_arguments		args;
	pthread_mutex_t	*mtx;
}					t_mutex_array;

//data structure for the status of each philosopher
typedef struct s_st
{
	int				end;
	int				*status;
	int				*hunger;
	int				*times_ate;
	long int		*timer;
	pthread_mutex_t	plock;
	pthread_mutex_t	lock;
	pthread_t		dh;
}					t_st;

//philisopher data
typedef struct s_pdata
{
	int				id;
	t_arguments		args;
	t_pthread_array	pta;
	t_mutex_array	mtxa;
	t_st			st;
}					t_pdata;

/*functions*/

/**********************/
/*       philo        */
/**********************/

//exit the program in a clean way
int			exiter(int type, t_pdata *pdata, t_pthread_array *pta,
				t_mutex_array *mtxa);

//create threads, mutexes and run a simulation to test these
int			main(int ac, char **av);

/**********************/
/*        init        */
/**********************/

//convert arguments into integer values and assign them to a structure
int			arg2struct(int ac, char **av, t_arguments *args);

//initialize mutexes
int			mk_mutexes(t_arguments *args, t_mutex_array *mtxa, t_pdata *pdata);

//initialize pthreads
int			mk_pthreads(t_arguments *args, t_pthread_array *pta,
				t_mutex_array *mtxa, t_pdata *pdata);

/**********************/
/*       logic        */
/**********************/

//check for deaths or when the simulation is supposed to end
int			end_handler(t_pdata *pdata);

//making sure the same fork can't be grabbed twice by mutex protection
void		status_handler(t_pdata *pdata, int lf, int rf);

//initialize the data behind the status, death and times ate handlers
int			init_checks(t_pdata *pdata);

//free any data associated with the indivdual philosophers
void		free_data(t_pdata *pdata);

//philisopher's behavior
void		*routine(void *pdata_ptr);

/**********************/
/*       utils        */
/**********************/

//very basic string to number conversion
int			micro_atoi(char *str);

//fetch the timestamp
long int	get_ts(t_pdata *pdata);

#endif
