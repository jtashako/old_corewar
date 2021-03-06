/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_scan_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 19:46:50 by smonroe           #+#    #+#             */
/*   Updated: 2019/02/18 01:41:22 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_scan_op(t_cycle *info, t_pc *pc)
{
	//ft_printf("at mem[%d] (%.2x) for %d more cycles\n", pc->i, info->mem[0][pc->i], pc->wait);
	t_pc	*tmp;
	t_mem	front[REG_SIZE];
	t_mem	back[REG_SIZE];

	tmp = pc;
	while (tmp)
	{
		tmp->i = MEM(tmp->i); //MEM_SIZE; //GOT RID OF BUFFER OVERFLOW ON WRAPAROUND BUT SHOULD THIS BE THE FIX???
		/*
		if (REG(info->mem[0][tmp->i].byte))
			tmp->wait--;
		else
			tmp->wait = -1;
			*/
		
		if (!REG(info->mem[0][tmp->i].byte))// < 1 || info->mem[0][tmp->i].byte > 16)
		{
			tmp->i = MEM(tmp->i + 1);
			if (REG(info->mem[0][tmp->i].byte)) /*THIS WORKS BUT SHOULD IT BE THIS WAY???*/
				tmp->wait = WAIT_MOD(info->mem[0][tmp->i].byte);
			else
				tmp->wait = -1;
			
			//tmp->wait = -1;
		}
		//else if (REG(info->mem[0][tmp->i].byte) //&& !tmp->wait)
		else //at OP
		{
			cw_memcp(front, &info->mem[0][0], REG_SIZE);
			cw_memcp(back, &info->mem[0][MEM_SIZE], REG_SIZE);
			if (!tmp->wait--)
				g_op_fn[info->mem[0][tmp->i].byte](info, tmp);
			tmp->i = MEM(tmp->i); //MEM_SIZE; //GOT RID OF BUFFER OVERFLOW ON WRAPAROUND BUT SHOULD THIS BE THE FIX???
			if (ft_memcmp(front, &info->mem[0][0], sizeof(front)))
				cw_memcp(&info->mem[0][MEM_SIZE], &info->mem[0][0], REG_SIZE);
			if (ft_memcmp(back, &info->mem[0][MEM_SIZE], sizeof(back)))
				cw_memcp(&info->mem[0][0], &info->mem[0][MEM_SIZE], REG_SIZE);
			if (REG(info->mem[0][tmp->i].byte)) /*THIS WORKS BUT SHOULD IT BE THIS WAY???*/
				tmp->wait = WAIT_MOD(info->mem[0][tmp->i].byte);
			else
			{
				//tmp->i = MEM(tmp->i + 1);
				tmp->wait = -1;
			}
		}
		//if (tmp->wait < 0 && REG(info->mem[0][tmp->i].byte))
			//tmp->wait = WAIT_MOD(info->mem[0][tmp->i].byte);
//		else
//			tmp->i = MEM(tmp->i + 1);
		info->mem[0][tmp->i].active = (info->mem[0][tmp->i].active == 0) ? 1 : info->mem[0][tmp->i].active;
		tmp = tmp->next;
	}
}

//Gagnant Notes: live ld add sub zjmp sti fork
