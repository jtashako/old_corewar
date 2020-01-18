/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_breakdown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:19:10 by jochang           #+#    #+#             */
/*   Updated: 2019/02/15 16:19:12 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/gui.h"

static void	print_dash(t_ncrs *ncrs, int offset, int i, int p)
{
	int		k;

	k = -1;
	wattron(ncrs->infowin, COLOR_PAIR(i));
	while (++k < p && offset + k <= 50)
		mvwprintw(ncrs->infowin, ncrs->init_y, ncrs->init_x + offset + k, "-");
	wattroff(ncrs->infowin, COLOR_PAIR(i));
}

static int get_lim(t_cycle *cycle, uint8_t w)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (++i < cycle->num_champs)
		if (!w)
		{
			if (cycle->current_live[i])
				n++;
		}
		else if (cycle->prev_live[i])
			n++;
	return (50 + (n >> 1));
}

void	print_breakdown(t_ncrs *ncrs, t_cycle *cycle, uint8_t w)
{
	int		i;
	int		p;
	int		lim;
	int		offset;

	i = -1;
	lim = get_lim(cycle, w);
	offset = 1;
	wattron(ncrs->infowin, GRAY_TEXT);
	PRINT_INFO(INIT_BRACKETS);
	INIT_LINE;
	if (cycle->breakdown[w])
	{
		while (++i < cycle->num_champs)
		{
			if (LIVE_COUNT && cycle->breakdown[w])
			{
				p = LIVE_COUNT * lim / cycle->breakdown[w];
				print_dash(ncrs, offset, i + 1, p);
				offset += p;
			}
		}
	}
	wattroff(ncrs->infowin, GRAY_TEXT);
}