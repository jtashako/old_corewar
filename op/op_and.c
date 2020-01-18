/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:13 by jochang           #+#    #+#             */
/*   Updated: 2019/05/08 03:49:26 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

//needs work
void	op_and(t_cycle *info, t_pc *pc)//imp
{
	TEA;
	int32_t	d1;
	int32_t	d2;
	int16_t	loc;
	uint8_t	acb;
	//ft_printf("%d------[AND]\n", pc->r[0]);
	d1 = 0;
	d2 = 0;
	acb = info->mem[0][MEM(pc->i + 1)].byte;
//	 for (int i = 0; i < 5; i++)
//	 	ft_printf("%02x ", info->mem[0][MEM(pc->i + i)].byte);
//	 ft_printf("\n");
	if ((acb >> 6) == REG_CODE)
		ft_memrcpy(&d1, &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE);//d1 = pc->r[info->mem[0][MEM[pc->i + 2)].byte];
	else if ((acb >> 6) == IND_CODE)
	{
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		cw_memren(&d1, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if ((acb >> 6) == DIR_CODE)
		cw_memren(&d1, &info->mem[0][MEM(pc->i + 2)], DIR_SIZE);
	else
	{
		pc->i = MEM(pc->i + acb_len(acb, 0));
		//pc->carry = 0;
		return ;
	}
	if (((acb >> 4) & 3) == REG_CODE)
	{ //DEBUG HERE
//		printf("copy reg[%d]{%08x} to d2, byte offset [%d]{%02x}\n", info->mem[0][MEM(pc->i + 1 + ACB_ARG(acb >> 6))].byte, info->mem[0][MEM(pc->i + 1 + ACB_ARG(acb >> 6))].byte,
//			   ACB_ARG(acb >> 6), ACB_ARG(acb >> 6));
//		d2 = pc->r[info->mem[0][MEM(pc->i + 1 + ACB_ARG(abc >> 6))].byte];
		ft_memrcpy(&d2, &pc->r[info->mem[0][MEM(pc->i + 1 + ACB_ARG(acb >> 6))].byte], REG_SIZE);
	} //END DEBUG
	else if (((acb >> 4) & 3) == IND_CODE)
	{
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 1 + ACB_ARG(acb >> 6))], IND_SIZE);
		cw_memren(&d2, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if (((acb >> 4) & 3) == DIR_CODE)
		cw_memren(&d2, &info->mem[0][MEM(pc->i + 1 + ACB_ARG(acb >> 6))], DIR_SIZE);
	else
	{
		pc->i = MEM(pc->i + acb_len(acb, 0));
		//pc->carry = 0;
		return ;
	}
	loc = acb_len(acb, 0);
	if (REG(info->mem[0][MEM(pc->i + loc - 1)].byte))
	{
//		ft_printf("d1: %d %x d2: %d %x\n", d1, d1, d2, d2);
		d1 &= d2;
//		ft_printf("Storing [%d][%x]\n", d1, d1);
		ft_memrcpy(&pc->r[info->mem[0][MEM(pc->i + loc - 1)].byte], &d1, REG_SIZE);
	}
	else
	{
		pc->i = MEM(pc->i + acb_len(acb, 0));
		pc->carry = 0;
		return ;
	}
	pc->carry = d1 ? 0 : 1;
	//pc->i += loc;
	pc->i = MEM(pc->i + loc);
	TIME("op_and\t");
}

/*
//OLD COPY INCASE I FUCK UP---------------------------------
//needs work
void	op_and(t_cycle *info, t_pc *pc)//imp
{
	TEA;
	int32_t	d1;
	int32_t	d2;
	int16_t	loc;
	uint8_t		acb;
	//ft_printf("%d------[AND]\n", pc->r[0]);
	d1 = 0;
	d2 = 0;
	acb = info->mem[0][MEM(pc->i + 1)].byte;
	for (int i = 0; i < 5; i++)
		ft_printf("%02x ", info->mem[0][MEM(pc->i + i)].byte);
	ft_printf("\n");
	if ((acb >> 6) == REG_CODE)
		ft_memrcpy(&d1, &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE);
	else if ((acb >> 6) == IND_CODE)
	{
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		cw_memren(&d1, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if ((acb >> 6) == DIR_CODE)
		cw_memren(&d1, &info->mem[0][MEM(pc->i + 2)], DIR_SIZE);
	if (((acb >> 4) & 3) == REG_CODE)
	{ //DEBUG HERE
		printf("copy reg[%d]{%08x} to d2, byte offset [%d]{%02x}\n", info->mem[0][MEM(pc->i + ACB_ARG((acb >> 4) & 3))].byte, info->mem[0][MEM(pc->i + ACB_ARG((acb >> 4) & 3))].byte,
			   ACB_ARG((acb >> 4) & 3), ACB_ARG((acb >> 4) & 3));
		ft_memrcpy(&d2, &pc->r[info->mem[0][MEM(pc->i + ACB_ARG((acb >> 4) & 3) + 1)].byte], REG_SIZE);
	} //END DEBUG                                                              ^^^^
	else if (((acb >> 4) & 3) == IND_CODE)
	{
		cw_memren(&loc, &info->mem[0][MEM(pc->i + ACB_ARG((acb >> 4) & 3))], IND_SIZE);
		cw_memren(&d2, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if (((acb >> 4) & 3) == DIR_CODE)
		cw_memren(&d2, &info->mem[0][MEM(pc->i + ACB_ARG((acb >> 4) & 3))], DIR_SIZE);
	loc = acb_len(acb, bool);
	if (REG(info->mem[0][MEM(pc->i + loc - 1)].byte))
	{
		ft_printf("d1[%08x] & d2[%08x]: %d\n", d1, d2, d1 & d2);
		pc->r[info->mem[0][MEM(pc->i + loc - 1)].byte] = d1 & d2;
		ft_printf("reg[1]: %8x\n", pc->r[1]);
		ft_printf("reg[%d]: %08x\n", info->mem[0][MEM(pc->i + loc - 1)].byte, pc->r[info->mem[0][MEM(pc->i + loc - 1)].byte]);
	}
	pc->carry = (d1 & d2) ? 0 : 1;
	pc->i += loc;
	TIME("op_and\t");
}

*/
