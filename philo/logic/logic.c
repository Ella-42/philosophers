/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:38:33 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/25 19:14:15 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//check for deaths or when the simulation is supposed to end
void	*end_handler(void *pdata_ptr)
{
	t_pdata	*pdata;
	int		i;

	pdata = (t_pdata *)pdata_ptr;
	usleep(1000);
	while (pdata->st.end != END)
	{
		if (pthread_mutex_lock(&pdata->st.lock) != 0)
			printf("Mutex lock error inside death handler for philosopher %i\n",
				pdata->id);
		i = -1;
		while (i < pdata->args.p_nb - 1)
		{
			if ((get_ts(pdata) - pdata->st.timer[i++]) >= pdata->args.t2d)
			{
				printf("%ld %i died\n", get_ts(pdata), i + 1);
				pdata->st.end = END;
			}
		}
		if (pdata->st.times_ate[pdata->id - 1] == pdata->args.loop_nb)
			pdata->st.end = END;
		if (pthread_mutex_unlock(&pdata->st.lock) != 0)
			printf("Mutex unlock error inside death handler"
				"for philosopher %i\n", pdata->id);
	}
	return (NULL);
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
	pdata->st.status[pdata->id - 1] = EATING;
	printf("%ld %i is eating\n", get_ts(pdata), pdata->id);
	usleep(pdata->args.t2e * 1000);
	pdata->st.timer[pdata->id - 1] = get_ts(pdata);
	if (pthread_mutex_unlock(&pdata->mtxa.mtx[lf - 1]) != 0)
		printf("Mutex unlock error on fork %i\n", lf);
	if (pthread_mutex_unlock(&pdata->mtxa.mtx[rf - 1]) != 0)
		printf("Mutex unlock error on fork %i\n", rf);
	pdata->st.times_ate[pdata->id - 1] += 1;
	pdata->st.status[pdata->id - 1] = SLEEPING;
	printf("%ld %i is sleeping\n", get_ts(pdata), pdata->id);
	usleep(pdata->args.t2s * 1000);
	pdata->st.status[pdata->id - 1] = THINKING;
	printf("%ld %i is thinking\n", get_ts(pdata), pdata->id);
}

//initialize the data behind the status, death and times ate handlers
void	init_checks(t_pdata *pdata)
{
	pdata->st.status = (int *)malloc(sizeof(int) * pdata->args.p_nb);
	pdata->st.hunger = (int *)malloc(sizeof(int) * pdata->args.p_nb);
	pdata->st.times_ate = (int *)malloc(sizeof(int) * pdata->args.p_nb);
	pdata->st.timer = (long int *)malloc(sizeof(long int) * pdata->args.p_nb);
	if ((!pdata->st.timer) || (!pdata->st.status) || (!pdata->st.times_ate))
		error(MEM, pdata);
	if (pthread_mutex_init(&pdata->st.lock, NULL))
		error(MEM, pdata);
	pdata->st.status[pdata->id - 1] = THINKING;
	pdata->st.hunger[pdata->id - 1] = HUNGRY;
	pdata->st.times_ate[pdata->id - 1] = 0;
	pdata->st.timer[pdata->id - 1] = 0;
	pdata->st.end = RUNNING;
}

//free any data associated with the indivdual philosophers
void	free_data(t_pdata *pdata)
{
	pthread_mutex_destroy(&pdata->st.lock);
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
	if (pdata == NULL)
		error(MEM, pdata);
	init_checks(pdata);
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
