/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debris.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:22:05 by jochang           #+#    #+#             */
/*   Updated: 2019/02/12 22:22:05 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/splash_screen.h"

static char	debris_type(double z)
{
	if (z > 40)
		return ('.');
	else if (z > 20)
		return ('o');
	return ('@');
}

void		add_debris(t_splash s, char *p, int timer, t_coord *debris)
{
	int		i;
	int		k;
	t_coord	d;
	int		x;
	int		y;

	i = timer - 6;
	k = 0;
	while (k < NUM_DEBRIS)
	{
		d.x = debris[k].x * i;
		d.y = debris[k].y * i;
		d.z = debris[k].z * i;
		if (!(d.z < 5 - PERSPECTIVE || d.z > PERSPECTIVE))
		{
			x = (s.cols / 2 + d.x * PERSPECTIVE / (d.z + PERSPECTIVE));
			y = (s.rows / 2 + d.y * PERSPECTIVE / (d.z + PERSPECTIVE));
			if (x >= 0 && x < s.cols && y >= 0 && y < s.rows)
				p[x + y * s.cols] = debris_type(d.z);
		}
		k++;
	}
}

t_coord		*make_debris(void)
{
	int		i;
	t_coord	*debris;
	t_coord	temp;
	double	tr;

	debris = malloc(NUM_DEBRIS * sizeof(t_coord));
	i = 0;
	while (i < NUM_DEBRIS)
	{
		temp.x = ft_prand();
		temp.y = ft_prand();
		temp.z = ft_prand();
		tr = sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
		debris[i].x = (temp.x / tr) * (1.3 + 0.2 * ft_prand());
		debris[i].y = (0.5 * temp.y / tr) * (1.3 + 0.2 * ft_prand());
		debris[i].z = (temp.z / tr) * (1.3 + 0.2 * ft_prand());
		i++;
	}
	return (debris);
}
