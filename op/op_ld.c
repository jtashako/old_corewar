/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:35 by jochang           #+#    #+#             */
/*   Updated: 2019/02/21 17:42:25 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_ld(t_cycle *info, t_pc *pc)
{
	uint8_t	reg;
	int16_t	loc;

	TEA;

	uint8_t		acb;
	acb = info->mem[0][MEM(pc->i + 1)].byte;

/*
	if (!REG(info->mem[0][MEM(pc->i + 3)].byte))
	{
		pc->i = MEM(pc->i + acb_len(acb, 0));
		return ;
	}
	*/
	//int arg1 = ((acb >> 6) & 3);
	if (((acb >> 4) & 3) != REG_CODE) //|| !REG(info->mem[0][MEM(pc->i + 2 + ACB_ARG(arg1))].byte)) this doesn't work
	{
	//	pc->i = MEM(pc->i + acb_len(acb, 0));
		pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
		return ;
	}
	if (((acb >> 6) & 3) == DIR_CODE)
	{
		reg = info->mem[0][MEM(pc->i + 6)].byte;
		if (REG(reg))
			cw_memren(&pc->r[reg], &info->mem[0][MEM(pc->i + 2)], REG_SIZE);
		else
		{ 
			pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
			//pc->i = MEM(pc->i + acb_len(acb, 0));
			//pc->carry = 0;
			return ;
		}
		//pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
		//pc->i = MEM(pc->i + acb_len(acb, 0));
		pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
		pc->carry = (pc->r[reg]) ? 0 : 1;
	}
	else if (((acb >> 6) & 3) == IND_CODE)
	{
		reg = info->mem[0][MEM(pc->i + 4)].byte;
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		if (REG(reg))
			cw_memren(&pc->r[reg], &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
		else
		{
			//pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
			//pc->i = MEM(pc->i + acb_len(acb, 0));
			pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
			//pc->carry = 0;
			return ;
		}
		//pc->i = MEM(pc->i + acb_len(acb, 0));
		pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
		pc->carry = (pc->r[reg]) ? 0 : 1;
	}
	else{
		pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
		//pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
		//pc->i = MEM(pc->i + acb_len(acb, 0));
		//pc->carry = 0;

	}
	TIME("op_ld\t");
}
