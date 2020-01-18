/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_rem_head.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:46:13 by jochang           #+#    #+#             */
/*   Updated: 2019/01/06 20:38:42 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_rem_head(t_pc **pc)
{
	t_pc	*tmp;

	tmp = NULL;
	if ((*pc)->next)
		tmp = (*pc)->next;
	ft_bzero(*pc, sizeof(*pc));
	//printf("rem_head: prev |%p| next |%p|\n", (*pc)->next, (*pc)->prev);
	free(*pc);
	*pc = tmp;
	if (*pc)
		(*pc)->prev = 0;
}
