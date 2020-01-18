/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_scan_rem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:48:09 by jochang           #+#    #+#             */
/*   Updated: 2019/02/15 16:42:46 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_scan_rem(t_pc **pc, t_cycle *info)
{
	t_pc	*tmp;

	tmp = *pc;
	while (tmp)
	{
		if (!tmp->alive)
		{
			info->pc_info[tmp->r[0]]--;
			pc_rem(&tmp);
		}
		else
			tmp = tmp->next;
	}
/*	while (tmp->next) //OLD CODE
	{
		tmp = tmp->next;
		if (!tmp->prev->alive)
			pc_rem(&tmp->prev);
	}
	if (!(*pc)->alive)
	pc_rem_head(pc);*/
}
