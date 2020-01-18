/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_infoblock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:18:19 by jochang           #+#    #+#             */
/*   Updated: 2019/02/12 22:18:21 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/gui.h"

static int	total_processes(t_cycle *cycle)
{
	int		i;
	int		total;

	i = -1;
	total = 0;
	while (++i < cycle->num_champs)
		total += cycle->pc_info[i];
	return (total);
}

static void	update_upper(t_ncrs *ncrs, t_cycle *cycle, t_flag *flag)
{
	PRINT_INFO_N("Cycles/second limit : %d", 1000000 / flag->w);
	ncrs->init_y += 2;
	PRINT_INFO_N("              Cycle : %d", cycle->cycle);
	ncrs->init_y += 2;
	PRINT_INFO_N("          Processes : %d", total_processes(cycle));
	ncrs->init_y += 2;
}

static void	update_players(t_ncrs *ncrs, t_cycle *cycle, t_head *head)
{
	int		i;

	i = -1;
	while (++i < cycle->num_champs)
	{
		PRINT_INFO_N("Player %d :", -(i + 1));
		wattron(ncrs->infowin, COLOR_PAIR(i + 1));
		mvwprintw(ncrs->infowin, ncrs->init_y, ncrs->init_x + 12, head[i].name);
		wattroff(ncrs->infowin, COLOR_PAIR(i + 1));
		ncrs->init_y++;
		PRINT_INFO_N("  Processes               : %d", cycle->pc_info[i]);
		ncrs->init_y++;
		PRINT_INFO_N("  Last live               : %d", cycle->last_live[i]);
		ncrs->init_y++;
		PRINT_INFO_N("  Lives in current period : %d", cycle->current_live[i]);
		ncrs->init_y += 2;
	}
}

static void	update_breakdown(t_ncrs *ncrs, t_cycle *cycle)
{
	PRINT_INFO("Live breakdown for current period :");
	ncrs->init_y++;
	print_breakdown(ncrs, cycle, 0);
	ncrs->init_y += 2;
	PRINT_INFO("Live breakdown for last period :");
	ncrs->init_y++;
	print_breakdown(ncrs, cycle, 1);
	ncrs->init_y += 2;
}

static void	update_lower(t_ncrs *ncrs)
{
	PRINT_INFO_N("CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
	ncrs->init_y += 2;
	PRINT_INFO_N(" CYCLE_DELTA : %d", CYCLE_DELTA);
	ncrs->init_y += 2;
	PRINT_INFO_N("    NBR_LIVE : %d", NBR_LIVE);
	ncrs->init_y += 2;
	PRINT_INFO_N("  MAX_CHECKS : %d", MAX_CHECKS);
}

void		update_infoblock(t_ncrs *ncrs, t_cycle *cycle, t_head *head, t_flag *flag)
{
	int		temp_num;

	temp_num = 42;
	ncrs->init_x = WINDOWS_OFFSET_LEFT;
	ncrs->init_y = 2;
	wattron(ncrs->infowin, A_BOLD);
	PRINT_INFO(ncrs->paused ? "** PAUSED ** " : "** RUNNING **");
	ncrs->init_y += 2;
	update_upper(ncrs, cycle, flag);
	update_players(ncrs, cycle, head);
	update_breakdown(ncrs, cycle);
	update_lower(ncrs);
	//show last live call as ascii art on bottom, or debug option screen
	wnoutrefresh(ncrs->infowin);
}

