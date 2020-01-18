/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:55 by jochang           #+#    #+#             */
/*   Updated: 2019/05/08 03:49:10 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_sti(t_cycle *info, t_pc *pc)
{
	int16_t		loc;
	int16_t		tmp;
	uint8_t		acb;

	TEA;
	acb = info->mem[0][MEM(pc->i + 1)].byte;
	//TOOK OUT REG CHECKS

	if (((acb >> 6) & 3) != REG_CODE || !REG(info->mem[0][MEM(pc->i + 2)].byte))
	{
		pc->i = MEM(pc->i + acb_len(acb, 1));
		return ;
	}

	/*
	if (!REG(info->mem[0][MEM(pc->i + 2)].byte))// || (acb >> 6) != REG_CODE)
	{
		printf("STI w/o 1st param as REG @ {%d, %d}\n", info->cycle, pc->i);
		pc->i = MEM(pc->i + acb_len(acb, 1));
		return ;
	}
	*/
	loc = 0;
	tmp = 0;
	int arg2 = ((acb >> 4) & 3);
	//if (REG(info->mem[0][MEM(pc->i + 3)].byte) && arg2 == REG_CODE)
	if (arg2 == REG_CODE)
		loc += pc->r[info->mem[0][MEM(pc->i + 3)].byte];
	else if (arg2 == DIR_CODE || arg2 == IND_CODE) //or DIR_CODE??
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
	else
	{
		//printf("STI w/ INVALID ACB FIRST ");
		pc->i = MEM(pc->i + acb_len(acb, 1));
		return ;
	}

	/*
	if (REG(info->mem[0][MEM(pc->i + 3)].byte) && ((acb >> 4) & 3) == REG_CODE)
		loc += pc->r[info->mem[0][MEM(pc->i + 3)].byte];
	else if (((acb >> 4) & 3) == DIR_CODE || ((acb >> 4) & 3) == IND_CODE)
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
	else
	{
		printf("STI w/ INVALID ACB FIRST ");
		pc->i = MEM(pc->i + acb_len(acb, 1));
		return ;
	}
	*/
	/*
	//this is wrong
	if ((acb & 0x0c) == (REG_CODE << 2) && REG(info->mem[0][MEM(pc->i + 3 + ACB_ARG_1((acb >> 4) & 3))].byte))
		loc += pc->r[info->mem[0][MEM(pc->i + 3 + ACB_ARG_1((acb >> 4) & 3))].byte];
	else if ((acb & 0x0c) == (DIR_CODE << 2))
		cw_memren(&tmp, &info->mem[0][MEM(pc->i + 3 + ACB_ARG_1((acb >> 4) & 3))], IND_SIZE);
	else
	{
		printf("STI w/ INVALID ACB SECOND");
		pc->i = MEM(pc->i + acb_len(acb, 1));
		return ;
	}
	*/
	int arg3 = ((acb >> 2) & 3);
	//arg2 is reg & reg exists at arg2
	if (arg3 == REG_CODE)// && REG(info->mem[0][MEM(pc->i + 3 + ACB_ARG_1(arg2))].byte))
		loc += pc->r[info->mem[0][MEM(pc->i + 3 + ACB_ARG_1(arg2))].byte];
	else if (arg3 == DIR_CODE || arg3 == IND_CODE) //OR DIR CODE??
		cw_memren(&tmp, &info->mem[0][MEM(pc->i + 3 + ACB_ARG_1(arg2))], IND_SIZE);
	else
	{
		//printf("STI w/ INVALID ACB SECOND");
		pc->i = MEM(pc->i + acb_len(acb, 1));
		return ;
	}


	loc += tmp;
	cw_memwen(&info->mem[0][MEM(pc->i + IDX((int16_t)loc))], &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE, pc->r[0]);
	//cw_memwen(&info->mem[0][MEM(pc->i + IDX(loc)], &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE, pc->r[0]);
	 //CHECK IF STORING IN PROPER REG
	 /*
	 if (info->cycle >= 4570 && info->cycle <= 4578)
	 {
		printf("STI is incrementing by %i\n", acb_len(acb, 1));
		printf("\tpc->i was %i, now %i\n", pc->i, pc->i + acb_len(acb, 1));
		//pc->i += acb_len(acb, bool);
	 }
	 */
	pc->i = MEM(pc->i + acb_len(acb, 1));
	//pc->i += acb_len(acb, bool);
	TIME("op_sti\t");
}
