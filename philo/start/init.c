/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:37:10 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/22 22:48:35 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//convert arguments into integer values and assign them to a structure
void	arg2struct(int ac, char **av, t_arguments *args)
{
	args->p_nb = micro_atoi(av[1]);
	args->f_nb = args->p_nb;
	args->t2d = micro_atoi(av[2]);
	args->t2e = micro_atoi(av[3]);
	args->t2s = micro_atoi(av[4]);
	if (ac == 6)
		args->loop_nb = micro_atoi(av[5]);
	else
		args->loop_nb = -1;
	args->time.start = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(args->time.start, NULL);
	args->time.end = (struct timeval *)malloc(sizeof(struct timeval));
}

//initialize mutexes
void	mk_mutexes(t_arguments *args, t_mutex_array *mtxa, t_pdata *pdata)
{
	int	i;

	mtxa->mtx = malloc(sizeof(pthread_mutex_t) * args->f_nb);
	if (!mtxa->mtx)
		error(MEM, pdata);
	i = 0;
	while (i < args->f_nb)
		if (pthread_mutex_init(&mtxa->mtx[i++], NULL))
			error(MEM, pdata);
}

//initialize pthreads
void	mk_pthreads(t_arguments *args, t_pthread_array *pta,
			t_mutex_array *mtxa, t_pdata *pdata)
{
	int		i;

	pta->pt = (pthread_t *)malloc(sizeof(pthread_t) * args->p_nb);
	if (!pta->pt)
		error(MEM, pdata);
	i = -1;
	while (i++ < args->p_nb - 1)
	{
		pdata = (t_pdata *)malloc(sizeof(t_pdata));
		if (!pdata)
			error(MEM, pdata);
		pdata->args = *args;
		pdata->mtxa = *mtxa;
		pdata->id = i + 1;
		if (pthread_create(&pta->pt[i], NULL, &routine, pdata))
			error(MEM, pdata);
	}
	if (pthread_create(&pdata->st.dh, NULL, &end_handler, pdata))
		error(MEM, pdata);
	i = 0;
	while (i < args->p_nb)
		pthread_join(pta->pt[i++], NULL);
	i = 0;
	while (i < args->f_nb)
		pthread_mutex_destroy(&mtxa->mtx[i++]);
}
