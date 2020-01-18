/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:59 by jochang           #+#    #+#             */
/*   Updated: 2019/02/21 17:42:55 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_live(t_cycle *info, t_pc *pc)//imp
{
	TEA;
	//ft_printf("%d-[ALIVE]\n", pc->r[0]);
	//set t_mem.active to 2 for live call instruction -smonroe DO THIS
	cw_memren(&info->last, &info->mem[0][MEM(pc->i + 1)], REG_SIZE);
	//info->last = pc->r[0];
	if (-info->last - 1 < MAX_PLAYERS && -info->last - 1 >= 0)
	{
		info->last_live[-info->last - 1] = info->cycle;
		info->pcount[-info->last - 1]++;
	}
	pc->alive++;
	pc->i = MEM(pc->i + 5);
	if (-info->last == pc->r[0])
	{
		info->mem[0][MEM(pc->i - 5)].active = 2;
		info->mem[0][MEM(pc->i - 5)].timer = FLASH_LEN << 1;
	}
	TIME("op_live\t");
}
/*
** If you call another players number is it an error?
** IF you play a non player number is it an error?
** How is this handled in 42vm? Make some champions to find out
*/