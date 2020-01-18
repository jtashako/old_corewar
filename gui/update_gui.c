/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:17:31 by jochang           #+#    #+#             */
/*   Updated: 2019/02/12 22:17:33 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/gui.h"

static void	update_border(t_ncrs *ncrs)
{
	wattron(ncrs->memwin, BORDER_COLOR);
	wattron(ncrs->infowin, BORDER_COLOR);
	wborder(ncrs->memwin, '*', '*', '*', '*', '*', '*', '*', '*');
	wborder(ncrs->infowin, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(ncrs->memwin, BORDER_COLOR);
	wattroff(ncrs->infowin, BORDER_COLOR);
}

static void	update_current_live(t_cycle *cycle)
{
	int		i;

	i = -1;
	if (cycle->cycle)
	{
		while (++i < cycle->num_champs)
		{
			if (cycle->last_live[i] == (uint32_t)cycle->cycle)
			{
				cycle->current_live[i]++;
				cycle->breakdown[0]++;
			}
		}
		if (!(cycle->cycle % CYCLE_TO_DIE))
		{
			i = -1;
			while (++i < cycle->num_champs)
			{
				cycle->prev_live[i] = cycle->current_live[i];
				cycle->current_live[i] = 0;
			}
			cycle->breakdown[1] = cycle->breakdown[0];
			cycle->breakdown[0] = 0;
		}
	}
}

void	update_gui(t_ncrs *ncrs, t_cycle *cycle, t_head *head, t_flag *flag)
{
	if (getch() == ' ')
		ncrs->paused = 1;
	update_border(ncrs);
	update_memblock(ncrs, cycle, flag);
	//if -g, gaetan face. else update infoblock
	update_current_live(cycle);
	update_infoblock(ncrs, cycle, head, flag);
	doupdate();
	while (ncrs->paused)
		if (getch() == ' ')
			ncrs->paused = 0;
}