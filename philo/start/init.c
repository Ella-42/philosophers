/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:37:10 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/21 19:00:29 by lpeeters         ###   ########.fr       */
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
void	arg2struct(char **av, t_arguments *args, int ac)
{
	args->p_nb = micro_atoi(av[1]);
	args->f_nb = args->p_nb;
	args->t2d = micro_atoi(av[2]);
	args->t2e = micro_atoi(av[3]);
	args->t2s = micro_atoi(av[4]);
	if (ac == 6)
		args->loop_nb = micro_atoi(av[5]);
}

//testing
void	*test(void *arg)
{
	(void)arg;
	return (NULL);
}

//initialize pthreads
void	mk_pthreads(t_arguments *args, t_pthread_array *pta)
{
	int	i;

	pta->pt = malloc(sizeof(t_pthread) * args->p_nb);
	i = 0;
	while (i < args->p_nb)
		pthread_create(&pta->pt[i++].thread, NULL, test, NULL);
	i = 0;
	while (i < args->p_nb)
		pthread_join(pta->pt[i++].thread, NULL);
}
