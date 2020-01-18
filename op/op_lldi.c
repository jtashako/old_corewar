/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:14 by jochang           #+#    #+#             */
/*   Updated: 2019/05/04 00:34:55 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_lldi(t_cycle *info, t_pc *pc)
{
	int32_t		loc;
	int32_t		tmp;
	uint8_t		acb;

	TEA;
	//ft_printf("%d--------------[LLDI]\n", pc->r[0]);
	acb = info->mem[0][MEM(pc->i + 1)].byte;
	loc = 0;
	tmp = 0;
	if ((acb >> 6) == REG_CODE)
		loc += pc->r[info->mem[0][MEM(pc->i + 2)].byte];
	else if ((acb >> 6) == DIR_CODE || (acb >> 6) == IND_CODE)
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
	else
	{
		pc->i = MEM(pc->i + acb_len(acb, 1));
		//pc->carry = 0;
		return ;
	}
	if ((acb & 0x30) == (REG_CODE << 4))
		loc += pc->r[info->mem[0][MEM(pc->i + 2 + ACB_ARG_1(acb >> 6))].byte];
	else if (((acb & 0x30) == (DIR_CODE << 4)) || ((acb & 0x30) == (IND_CODE << 4)))
		cw_memren(&tmp, &info->mem[0][MEM(pc->i + 2 + ACB_ARG_1(acb >> 6))], IND_SIZE);
	else
	{
		pc->i = MEM(pc->i + acb_len(acb, 1));
		//pc->carry = 0;
		return ;
	}
	loc += tmp;
	tmp = info->mem[0][MEM(pc->i + acb_len(acb, 1) - 1)].byte;
	//ft_printf("%d as loc and for tmp %d\n", loc, tmp);
	if (REG(tmp))
		cw_memren(&pc->r[tmp], &info->mem[0][MEM(pc->i + (int16_t)loc)], REG_SIZE);
	else
	{
		pc->i = MEM(pc->i + acb_len(acb, 1));
		//pc->carry = 0;
		return ;
	}

	pc->i = MEM(pc->i + acb_len(acb, 1));
	pc->carry = (pc->r[tmp]) ? 0 : 1;
	TIME("op_lld\t");
}
