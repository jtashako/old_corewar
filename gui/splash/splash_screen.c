/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:25:31 by jochang           #+#    #+#             */
/*   Updated: 2019/02/12 22:25:32 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/splash_screen.h"

static void		splash_background(t_splash s, char *p, int timer, t_coord *debris)
{
	explosion(s, p, timer);
	if (timer > 6)
		add_debris(s, p, timer, debris);
	mvwaddstr(s.win, 0, 0, p);
}

static t_splash	getminmax(void)
{
	t_splash	s;

	getmaxyx(stdscr, s.rows, s.cols);
	s.minx = -s.cols / 2;
	s.maxx = s.cols + s.minx - 1;
	s.miny = -s.rows / 2;
	s.maxy = s.rows + s.miny - 1;
	return (s);
}

void			splash_screen(void)
{
	t_splash	s;
	int			timer;
	t_coord		*debris;
	char		*p;

	s = getminmax();
	timer = 0;
	s.win = newwin(s.rows, s.cols, 0, 0);
	debris = make_debris();
	p = malloc(s.rows * s.cols + 1);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	while (timer < NUM_FRAMES)
	{
		splash_background(s, p, timer, debris);
		splash_name(s);
		wrefresh(s.win);
		timer++;
		usleep(DELAY);
	}
	free(debris);
	free(p);
	delwin(s.win);
}
