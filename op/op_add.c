/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:58:58 by jochang           #+#    #+#             */
/*   Updated: 2019/05/08 22:02:32 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_add(t_cycle *info, t_pc *pc)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	c;

	uint8_t		acb;
	acb = info->mem[0][MEM(pc->i + 1)].byte;

	TEA;
	a = info->mem[0][MEM(pc->i + 2)].byte;
	b = info->mem[0][MEM(pc->i + 3)].byte;
	c = info->mem[0][MEM(pc->i + 4)].byte;
	if ((acb == 0x54 || acb == 0x55 || acb == 0x56 || acb == 0x57) && REG(a) && REG(b) && REG(c))
	{
		pc->r[c] = pc->r[b] + pc->r[a];
		pc->i = MEM(pc->i + acb_len(acb,0));
		if (pc->r[c])
			pc->carry = 0;
		else
			pc->carry = 1;
		//pc->carry = 1;
	}
	else
	{
		//pc->carry = 0;
		pc->i = MEM(pc->i + acb_len(acb,0));
	}
	TIME("op_add\t");
}
