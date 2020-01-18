/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:46 by jochang           #+#    #+#             */
/*   Updated: 2019/05/08 22:02:19 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_st(t_cycle *info, t_pc *pc)//imp
{
	int16_t		loc;
	uint8_t		acb;

	TEA;
	acb = info->mem[0][MEM(pc->i + 1)].byte;
	//REQUIRED FN. (f3.cor\!) 03 w/ acb 06 && f3.cor3
	//skip by acb in 1st 2 param .. ignore the rest
	if (!REG(info->mem[0][MEM(pc->i + 2)].byte))
	{
		pc->i = MEM(pc->i + 2);
		return ;
	}

//		printf("ST : cycle is %i\n", info->cycle);
	//ft_printf("%d---[ST]\n", pc->r[0]);
	if (((acb >> 6) & 3) != REG_CODE)
	{
		pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
		return ;
	}
	if (((acb >> 4) & 3) == REG_CODE)
	{
		pc->r[info->mem[0][MEM(pc->i + 3)].byte] = pc->r[info->mem[0][MEM(pc->i + 2)].byte];
		pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
	}
	else if (((acb >> 4) & 3) == IND_CODE)
	{
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
		cw_memwen(&info->mem[0][MEM(pc->i + IDX(loc))], &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE, pc->r[0]);
		pc->i = MEM(pc->i + acb_len((acb >> 2), 0));
	}
	else
	{
		ft_printf("Store has an INVALID ACB {%2x}", acb);
		//pc->i = MEM(pc->i + 2);
		pc->i = MEM(pc->i + acb_len((acb >> 2), 0)); //ignore last 2 bytes of acb
		/*
		pc->i = MEM(pc->i + 3);
		if (((acb >> 6) & 3) == 1)
			pc->i = MEM(pc->i + 1);
		else if (((acb >> 6) & 3) == 2)
			pc->i = MEM(pc->i + 4);
		else if (((acb >> 6) & 3) == 3)
			pc->i = MEM(pc->i + 2);
			*/
	
		//pc->i = MEM(pc->i + acb_len(acb, 0));
	}
		//pc->i = MEM(pc->i + 5);
		//pc->i = MEM(pc->i + acb_len(acb, 1));

		//pc->i++;
	TIME("op_sti\t");
}
