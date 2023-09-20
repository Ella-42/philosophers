/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:38:33 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/20 23:50:39 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//making sure the same fork can't be grabbed twice by mutex protection
void	fork_handler(t_pdata *pdata, int lf, int rf)
{
	if (pdata->id % 2 != 0)
		usleep(1000);
	if (pthread_mutex_lock(&pdata->mtxa.mtx[lf - 1]) != 0)
		printf("Mutex lock error on fork %i\n", lf);
	printf("%ld %i has taken fork %i\n", get_ts(pdata), pdata->id, lf);
	if (pthread_mutex_lock(&pdata->mtxa.mtx[rf - 1]) != 0)
		printf("Mutex lock error on fork %i\n", rf);
	printf("%ld %i has taken fork %i\n", get_ts(pdata), pdata->id, rf);
	printf("%ld %i is eating\n", get_ts(pdata), pdata->id);
	usleep(pdata->args.t2e * 1000);
	if (pthread_mutex_unlock(&pdata->mtxa.mtx[lf - 1]) != 0)
		printf("Mutex unlock error on fork %i\n", lf);
	//printf("%ld %i dropped fork %i\n", get_ts(pdata), pdata->id, lf);
	if (pthread_mutex_unlock(&pdata->mtxa.mtx[rf - 1]) != 0)
		printf("Mutex unlock error on fork %i\n", rf);
	//printf("%ld %i dropped fork %i\n", get_ts(pdata), pdata->id, rf);
	printf("%ld %i is sleeping\n", get_ts(pdata), pdata->id);
	usleep(pdata->args.t2s * 1000);
}

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
	while (1)
		fork_handler(pdata, lf, rf);
	free(pdata);
	return (NULL);
}
