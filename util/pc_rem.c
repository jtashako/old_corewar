/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_rem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:09:26 by jochang           #+#    #+#             */
/*   Updated: 2019/02/15 16:43:24 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_rem(t_pc **pc)
{
	t_pc *tmp;

	if (!pc)
		return ;
	if ((*pc)->next)
		(*pc)->next->prev = (*pc)->prev;
	if ((*pc)->prev)
		(*pc)->prev->next = (*pc)->next;
	else
		g_head = (*pc)->next;
	tmp = (*pc)->next;
	ft_bzero(*pc, sizeof(**pc));
	free(*pc);
	*pc = tmp;
}
