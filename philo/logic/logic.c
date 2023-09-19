/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:38:33 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/20 01:29:54 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

	//printf("philosopher %i with fork %i on their right"
		//" and fork %i on their left\n", pdata->id, rf, lf);

//making sure the same fork can't be grabbed twice by mutex protection
void	fork_handler(t_pdata *pdata, int lf, int rf)
{
	if (pthread_mutex_lock(&pdata->mtxa.mtx[lf - 1]) != 0)
		printf("Mutex lock error on fork %i\n", lf);
	printf("Philosopher %i has taken fork %i\n", pdata->id, lf);
	if (pthread_mutex_lock(&pdata->mtxa.mtx[rf - 1]) != 0)
		printf("Mutex lock error on fork %i\n", rf);
	printf("Philosopher %i has taken fork %i\n", pdata->id, rf);
	printf("Philosopher %i is eating\n", pdata->id);
	usleep(200000);
	if (pthread_mutex_unlock(&pdata->mtxa.mtx[lf - 1]) != 0)
		printf("Mutex unlock error on fork %i\n", lf);
	printf("Philosopher %i dropped fork %i\n", pdata->id, lf);
	if (pthread_mutex_unlock(&pdata->mtxa.mtx[rf - 1]) != 0)
		printf("Mutex unlock error on fork %i\n", rf);
	printf("Philosopher %i dropped fork %i\n", pdata->id, rf);
}

	//printf("time to eat in microseconds: %i\n", pdata->args.t2e * 100);

//philisopher's behavior
void	*routine(void *pdata_ptr)
{
	t_pdata	*pdata;
	int		rf;
	int		lf;

	pdata = (t_pdata *)pdata_ptr;
	if (pdata == NULL)
		error(MEM, pdata);
	rf = pdata->id - 1;
	lf = pdata->id;
	if (pdata->id == 1)
		rf = pdata->args.p_nb;
	fork_handler(pdata, lf, rf);
	gettimeofday(pdata->args.time.end, NULL);
	printf("Elapsed time: %ld miliseconds\n", ((pdata->args.time.end->tv_sec
				- pdata->args.time.start->tv_sec) * 1000000L
			+ (pdata->args.time.end->tv_usec - pdata->args.time.start->tv_usec))
		/ 1000);
	free(pdata);
	return (NULL);
}
