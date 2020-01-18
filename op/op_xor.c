/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:01:09 by jochang           #+#    #+#             */
/*   Updated: 2019/05/04 00:34:07 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_xor(t_cycle *info, t_pc *pc)
{
	int32_t	d1;
	int32_t	d2;
	int16_t	loc;
	uint8_t		acb;

	d1 = 0;
	d2 = 0;
	acb = info->mem[0][MEM(pc->i + 1)].byte;
	if ((acb >> 6) == REG_CODE)
		ft_memrcpy(&d1, &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE);
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
		ft_memrcpy(&d2, &pc->r[info->mem[0][MEM(pc->i + ACB_ARG(acb >> 6))].byte], REG_SIZE);
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
		pc->r[info->mem[0][MEM(pc->i + loc - 1)].byte] = d1 ^ d2;
	else
	{
		pc->i = MEM(pc->i + acb_len(acb, 0));
		//pc->carry = 0;
		return ;
	}
	pc->carry = (d1 ^ d2) ? 0 : 1;
	pc->i = MEM(pc->i + loc);
}
