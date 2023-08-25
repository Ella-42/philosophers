/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:38:33 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/25 19:34:19 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//philisopher's behavior
void	*routine(void *pdata_ptr)
{
	t_pdata	*pdata;
	int		p_id;
	int		rf;
	int		lf;

	pdata = (t_pdata *)pdata_ptr;
	p_id = pdata->id;
	rf = p_id - 1;
	lf = p_id;
	if (p_id == 1)
		rf = 5;
	printf("philosopher: %i, with fork: %i on their right"
		" and fork %i on their left\n", pdata->id, rf, lf);
	return (NULL);
}
