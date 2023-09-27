/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:37:10 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/28 00:57:44 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//convert arguments into integer values and assign them to a structure
int	arg2struct(int ac, char **av, t_arguments *args)
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
	if (!args->p_nb || !args->t2d || !args->t2e || !args->t2s || !args->loop_nb)
		return (exiter(ARGUMENT, NULL, NULL, NULL));
	return (0);
}

//initialize mutexes
int	mk_mutexes(t_arguments *args, t_mutex_array *mtxa, t_pdata *pdata)
{
	int	i;

	mtxa->mtx = malloc(sizeof(pthread_mutex_t) * args->f_nb);
	if (!mtxa->mtx)
		return (exiter(1, NULL, NULL, NULL));
	i = 0;
	while (i < args->f_nb)
		if (pthread_mutex_init(&mtxa->mtx[i++], NULL))
			return (1);
	pdata->args.time.start = (struct timeval *)malloc(sizeof(struct timeval));
	pdata->args.time.end = (struct timeval *)malloc(sizeof(struct timeval));
	if ((!pdata->args.time.start) || (!pdata->args.time.end))
		return (exiter(MEM, pdata, NULL, NULL));
	gettimeofday(pdata->args.time.start, NULL);
	mtxa->args = pdata->args;
	return (0);
}

//initialize pthreads
int	mk_pthreads(t_arguments *args, t_pthread_array *pta,
			t_mutex_array *mtxa, t_pdata *pdata)
{
	int		i;

	pta->pt = (pthread_t *)malloc(sizeof(pthread_t) * args->p_nb);
	if (!pta->pt)
		return (exiter(MEM, pdata, NULL, NULL));
	i = -1;
	while (i++ < args->p_nb - 1)
	{
		pdata = (t_pdata *)malloc(sizeof(t_pdata));
		if (!pdata)
			return (exiter(PDATA, NULL, pta, mtxa));
		pdata->args = *args;
		pdata->mtxa = *mtxa;
		pdata->id = i + 1;
		if (pthread_create(&pta->pt[i], NULL, &routine, pdata))
			return (exiter(PDATA, pdata, pta, mtxa));
	}
	while (!end_handler(pdata))
		;
	i = 0;
	while (i < args->f_nb)
		pthread_mutex_destroy(&mtxa->mtx[i++]);
	return (0);
}
