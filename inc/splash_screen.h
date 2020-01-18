/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash_screen.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:21:26 by jochang           #+#    #+#             */
/*   Updated: 2019/02/12 22:21:28 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLASH_SCREEN_H
# define SPLASH_SCREEN_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <curses.h>
#include <locale.h>

# define NUM_FRAMES 100
# define DELAY 25000
# define NUM_DEBRIS 800
# define PERSPECTIVE 50.0
# define SN(x, w) mvwprintw(s.win, s.rows / 2 + ch, (s.cols - 85) / 2 + x, w)

typedef struct	s_coord
{
	double		x;
	double		y;
	double		z;
}				t_coord;

typedef struct	s_splash
{
	WINDOW		*win;
	int			rows;
	int			cols;
	int			minx;
	int			maxx;
	int			miny;
	int			maxy;

}				t_splash;

void		splash_screen(void);
t_coord		*make_debris(void);
void		add_debris(t_splash s, char *p, int timer, t_coord *debris);
void		explosion(t_splash s, char *p, int timer);
void		splash_name(t_splash s);
double		ft_prand(void);

#endif
