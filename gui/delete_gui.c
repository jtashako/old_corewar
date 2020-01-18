/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_gui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:38:23 by jochang           #+#    #+#             */
/*   Updated: 2019/02/13 16:38:23 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/gui.h"

void	delete_gui(t_ncrs *ncrs)
{
	if (ncrs)
	{
		delwin(ncrs->memwin);
		delwin(ncrs->infowin);
		free(ncrs);
		endwin();
	}
}
