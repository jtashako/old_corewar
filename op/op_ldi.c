/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:44 by jochang           #+#    #+#             */
/*   Updated: 2019/05/08 03:49:02 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"
// needs work, rain.cor and Gangant.cor as examples. Gagnant better. Step 2800.
// seems to work in rain, Gagnant still not loading, need to check neighboring ops.
//read at address arg1 . add arg 2 to value and store in r3
void	op_ldi(t_cycle *info, t_pc *pc)
{
	int32_t		loc;
	int32_t		tmp;
	uint8_t		acb;

	TEA;
	//ft_printf("%d----------[LDI]\n", pc->r[0]);
	acb = info->mem[0][MEM(pc->i + 1)].byte;
	loc = 0;
	tmp = 0;
	/*
	//-----------------------------------------
	if (((acb >> 6) & 3) != IND_CODE)
	{
		pc->i = MEM(pc->i + acb_len(acb, 1));
		return ;
	}
	//-----------------------------------------
	*/

	if (((acb >> 6) & 3)== REG_CODE)
		loc = pc->r[info->mem[0][MEM(pc->i + 2)].byte]; //cpy from reg
	else if ((acb >> 6) == DIR_CODE || (acb >> 6) == IND_CODE)
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE); //cp from addr.
	else
	{
		pc->i = MEM(pc->i + acb_len(acb, 1));
		//printf("LDI INVALID ACB\n");
		//pc->carry = 0;
		//pc->i++;
		return ;
	}
	//loc has arg1
	
	int arg2 = ((acb >> 4) & 3);
		//printf("cycle is %i, arg2 is %i\n", info->cycle, arg2);
	//ft_printf("|%d| + ", loc);
	//if ((acb & 0x30) == (REG_CODE << 4))  //2nd arg is DIR OR IND? (not REg) (0x30 == 0011 0000)
	if (arg2 == REG_CODE)  //2nd arg is DIR OR IND? (not REg) (0x30 == 0011 0000)
		tmp = pc->r[info->mem[0][MEM(pc->i + 2 + ACB_ARG_1((acb >> 6) & 3))].byte];
//		tmp = pc->r[info->mem[0][(MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4)))].byte];
	//else if (((acb & 0x30) == (DIR_CODE << 4)) || ((acb & 0x30) == (IND_CODE << 4)))
	else if (arg2 == DIR_CODE || arg2 == IND_CODE)
	{
		//printf("cycle is %i, arg2 is %i\n", info->cycle, arg2);
	//else if (arg2 == 1 || arg2 == 2 || arg2 == 3)
		cw_memren(&tmp, &info->mem[0][MEM(pc->i + 2 + ACB_ARG_1((acb >> 4) & 3))], IND_SIZE);
	}
	else
	{
		//pc->i++;
		pc->i = MEM(pc->i + acb_len(acb, 1));
		//printf("LDI INVALID ACB\n");
		//pc->carry = 0;
		return ;
	}
	loc += tmp;
	//ft_printf("|%d| = |%d|\n", tmp, loc);

	//could be invalid register	
	tmp = info->mem[0][MEM(pc->i + acb_len(acb, 1) - 1)].byte; //register to store at
	//ft_printf("reg[%d]\n", tmp);
	if (REG(tmp))
	{
		//if (pc->i + loc < 4096)
			//cw_memren(&pc->r[tmp], &info->mem[0][MEM(pc->i + (int16_t)loc)], REG_SIZE);
		cw_memren(&pc->r[tmp], &info->mem[0][MEM(pc->i + IDX((int16_t)loc))], REG_SIZE);
	}
	else
	{
		//pc->i++;
		//printf("LDI HAS AN INVALID ACB ");
		pc->i = MEM(pc->i + acb_len(acb, 1));
		//pc->carry = 0;
		return ;
	}
	//ft_printf("Result: %08x\n", pc->r[tmp]);
	//ft_printf("IDX((int16_t)loc) == %d and loc == %d", IDX((int16_t)loc), loc);
	//pc->i += acb_len(acb, 1);
	pc->i = MEM(pc->i + acb_len(acb,1));
	//if result of adding two indices is 0 => set carry 1 else 0
	//pc->carry = (pc->r[c]) ? 0 : 1;
		//pc->carry = 0;

	if (loc)
		pc->carry = 0;
	else
		pc->carry = 1;
	
	TIME("op_ldi\t");
}
