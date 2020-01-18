/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:52 by jochang           #+#    #+#             */
/*   Updated: 2019/02/21 17:42:46 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

//TEST 
void	op_lfork(t_cycle *info, t_pc *pc)
{
	int16_t	addr;
	t_pc	*new;

	cw_memren(&addr, &info->mem[0][MEM(pc->i + 1)], IND_SIZE);
	new = pc_new(-pc->r[0], MEM(pc->i + addr), info->mem[0][MEM(pc->i + addr)].byte);
	ft_memcpy(&new->r, &pc->r, sizeof(new->r));
	new->carry = pc->carry;
	new->alive = pc->alive;
	pc_app(&g_head, new);
	pc->i = MEM(pc->i + 3);
	info->pc_info[pc->r[0]]++;
}
