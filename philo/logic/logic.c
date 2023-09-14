/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:38:33 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/14 23:34:14 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	printf("philosopher %i with fork %i on their right"
		" and fork %i on their left\n", pdata->id, rf, lf);
	if (pthread_mutex_lock(&pdata->mtxa.mtx[lf]) != 0)
		printf("Fork %i was already taken\n", lf);
	//if (pthread_mutex_lock(&pdata->mtxa.mtx[rf]) != 0)
		//printf("Fork %i was already taken\n", rf);
	//pthread_mutex_lock(&pdata->mtxa.mtx[lf]);
	//pthread_mutex_lock(&pdata->mtxa.mtx[rf]);
	//pthread_mutex_unlock(&pdata->mtxa.mtx[lf]);
	//pthread_mutex_unlock(&pdata->mtxa.mtx[rf]);
	free(pdata);
	return (NULL);
}
