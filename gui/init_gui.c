/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 03:26:48 by jochang           #+#    #+#             */
/*   Updated: 2019/03/14 14:27:46 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/gui.h"

static void		init_colors(t_ncrs *ncrs)
{
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_WHITE);
	init_pair(6, COLOR_BLUE, COLOR_WHITE);
	init_pair(7, COLOR_RED, COLOR_WHITE);
	init_pair(8, COLOR_CYAN, COLOR_WHITE);
	init_pair(20, COLOR_GRAY, COLOR_GRAY);
	init_pair(21, COLOR_GRAY, COLOR_BLACK);
	wattron(ncrs->memwin, A_BOLD);
	wattron(ncrs->infowin, A_BOLD);
}

t_ncrs			*init_gui(t_cycle *cycle, t_head *head, t_flag *flag)
{
	t_ncrs	*ncrs;

	ncrs = malloc(sizeof(t_ncrs));
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	curs_set(0);
	use_default_colors();
	ncrs->memwin = newwin(MEMWIN_HEIGHT, MEMWIN_WIDTH, 0, 0);
	ncrs->infowin = newwin(MEMWIN_HEIGHT, INFOWIN_WIDTH, 0, MEMWIN_WIDTH - 1);
	ncrs->paused = 1;
	nodelay(stdscr, TRUE);
	nodelay(ncrs->memwin, TRUE);
	nodelay(ncrs->infowin, TRUE);
//	splash_screen();
	init_colors(ncrs);
	update_gui(ncrs, cycle, head, flag);
	return (ncrs);
}
