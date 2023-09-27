/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:38:33 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/28 00:59:06 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//check for deaths or when the simulation is supposed to end
int	end_handler(t_pdata *pdata)
{
	pdata->st.end = RUNNING;
	while (pdata->st.end != END)
	{
		usleep(1000);
		if (pthread_mutex_lock(&pdata->st.lock) != 0)
			printf("Mutex lock error inside death handler\n");
		if ((get_ts(pdata) - *pdata->st.timer) >= pdata->args.t2d)
		{
			pdata->st.end = END;
			printf("%ld %i died\n", get_ts(pdata), 1);
			return (1);
		}
		if (*pdata->st.times_ate == pdata->args.loop_nb)
		{
			pdata->st.end = END;
			return (1);
		}
		if (pthread_mutex_unlock(&pdata->st.lock) != 0)
			printf("Mutex unlock error inside death handler\n");
	}
	return (0);
}

//making sure the same fork can't be grabbed twice by mutex protection
void	status_handler(t_pdata *pdata, int lf, int rf)
{
	if (pthread_mutex_lock(&pdata->mtxa.mtx[lf - 1]) != 0)
		printf("Mutex lock error on fork %i\n", lf);
	printf("%ld %i has taken a fork\n", get_ts(pdata), pdata->id);
	if (pthread_mutex_lock(&pdata->mtxa.mtx[rf - 1]) != 0)
		printf("Mutex lock error on fork %i\n", rf);
	printf("%ld %i has taken a fork\n", get_ts(pdata), pdata->id);
	*pdata->st.status = EATING;
	printf("%ld %i is eating\n", get_ts(pdata), pdata->id);
	usleep(pdata->args.t2e * 1000);
	*pdata->st.timer = get_ts(pdata);
	if (pthread_mutex_unlock(&pdata->mtxa.mtx[lf - 1]) != 0)
		printf("Mutex unlock error on fork %i\n", lf);
	if (pthread_mutex_unlock(&pdata->mtxa.mtx[rf - 1]) != 0)
		printf("Mutex unlock error on fork %i\n", rf);
	*pdata->st.times_ate += 1;
	*pdata->st.status = SLEEPING;
	printf("%ld %i is sleeping\n", get_ts(pdata), pdata->id);
	usleep(pdata->args.t2s * 1000);
	*pdata->st.status = THINKING;
	printf("%ld %i is thinking\n", get_ts(pdata), pdata->id);
}

//initialize the data behind the status, death and times ate handlers
int	init_checks(t_pdata *pdata)
{
	pdata->st.status = (int *)malloc(sizeof(int));
	pdata->st.hunger = (int *)malloc(sizeof(int));
	pdata->st.times_ate = (int *)malloc(sizeof(int));
	pdata->st.timer = (long int *)malloc(sizeof(long int));
	if ((!pdata->st.status) || (!pdata->st.hunger)
		|| (!pdata->st.times_ate) || (!pdata->st.timer)
		|| (pthread_mutex_init(&pdata->st.lock, NULL)))
		return (exiter(THREAD, pdata, NULL, NULL));
	*pdata->st.status = THINKING;
	*pdata->st.hunger = HUNGRY;
	*pdata->st.times_ate = 0;
	*pdata->st.timer = 0;
	return (0);
}

//free any data associated with the indivdual philosophers
void	free_data(t_pdata *pdata)
{
	int	i;

	pthread_mutex_destroy(&pdata->st.lock);
	i = 0;
	while (i < pdata->args.p_nb)
		pthread_detach(pdata->pta.pt[i++]);
	if (pdata->st.status)
		free(pdata->st.status);
	if (pdata->st.hunger)
		free(pdata->st.hunger);
	if (pdata->st.times_ate)
		free(pdata->st.times_ate);
	if (pdata->st.timer)
		free(pdata->st.timer);
	free(pdata);
}

//philisopher's behavior
void	*routine(void *pdata_ptr)
{
	t_pdata	*pdata;
	int		rf;
	int		lf;

	pdata = (t_pdata *)pdata_ptr;
	if (init_checks(pdata))
		return (NULL);
	rf = pdata->id - 1;
	lf = pdata->id;
	if (pdata->id == 1)
		rf = pdata->args.p_nb;
	if (pdata->id % 2 != 0)
		usleep(1000);
	while (pdata->st.end != END)
		status_handler(pdata, lf, rf);
	free_data(pdata);
	return (NULL);
}
