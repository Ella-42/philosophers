/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:37:10 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/25 19:42:11 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//very basic string to number conversion
int	micro_atoi(char *str)
{
	int		nb;
	char	*str_cpy;

	str_cpy = str;
	while (*str_cpy != '\0')
		if (*str_cpy < '0' || '9' < *str_cpy++)
			error(ARGUMENT);
	nb = 0;
	while (*str != '\0')
		nb = nb * 10 + (*str++ - 48);
	return (nb);
}

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
}

//initialize mutexes
void	mk_mutexes(t_arguments *args, t_mutex_array *mtxa)
{
	int	i;

	mtxa->mtx = malloc(sizeof(pthread_mutex_t) * args->f_nb);
	if (!mtxa->mtx)
		printf("handle this\n");
	i = 0;
	while (i < args->f_nb)
		pthread_mutex_init(&mtxa->mtx[i++], NULL);
}

//initialize pthreads
void	mk_pthreads(t_arguments *args, t_pthread_array *pta, t_main *main)
{
	int		i;
	t_pdata	*pdata;

	(void)main;
	pta->pt = (pthread_t *)malloc(sizeof(pthread_t) * args->p_nb);
	if (!pta->pt)
		printf("handle this\n");
	i = -1;
	while (i++ < args->p_nb - 1)
	{
		pdata = (t_pdata *)malloc(sizeof(t_pdata));
		if (!pdata)
			printf("handle this\n");
		pdata->id = i + 1;
		printf("id: %i\n", pdata->id);
		pthread_create(&pta->pt[i], NULL, routine, pdata);
	}
	i = 0;
	while (i < args->p_nb)
		pthread_join(pta->pt[i++], NULL);
}
