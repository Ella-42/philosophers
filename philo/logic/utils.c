/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:35 by lpeeters          #+#    #+#             */
/*   Updated: 2023/09/27 22:21:37 by lpeeters         ###   ########.fr       */
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
			return (0);
	nb = 0;
	while (*str != '\0')
		nb = nb * 10 + (*str++ - 48);
	return (nb);
}

//fetch the timestamp
long int	get_ts(t_pdata *pdata)
{
	gettimeofday(pdata->args.time.end, NULL);
	return (((pdata->args.time.end->tv_sec * 1000)
			+ (pdata->args.time.end->tv_usec / 1000))
		- ((pdata->args.time.start->tv_sec * 1000)
			+ (pdata->args.time.start->tv_usec / 1000)));
}
