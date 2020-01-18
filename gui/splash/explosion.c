/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explosion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:24:06 by jochang           #+#    #+#             */
/*   Updated: 2019/02/12 22:24:07 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/splash_screen.h"

static char	explosion_type(int v, int i)
{
	if (v < 0)
		return ((i < 19) ? "%@W#H=+~-:."[i - 8] : ' ');
	else if (v < 20)
		return (" .:!HIOMW#%$&@08O=+-"[v]);
	return (' ');
}

static void	calculate_explosion(char **p, t_coord c, int timer)
{
	c.z = sqrt(c.x * c.x + 4 * c.y * c.y);
	if (timer < 8)
		**p = (c.z < timer * 2) ? '@' : ' ';
	else
	{
		c.z = c.z * (0.5 + (ft_prand() / 3.0) * 
			cos(16. * atan2(c.y * 2. + 0.01, c.x + 0.01)) * .3);
		**p = explosion_type(timer - c.z - 7, timer);
	}
}

void	explosion(t_splash s, char *p, int timer)
{
	char	*top;
	double	t;
	t_coord	c;

	t = (1.0 * timer) / NUM_FRAMES;
	top = p;
	c.y = s.miny;
	while (c.y <= s.maxy)
	{
		c.x = s.minx;
		while (c.x <= s.maxx)
		{
			calculate_explosion(&p, c, timer);
			p++;
			c.x++;
		}
		c.y++;
	}
}