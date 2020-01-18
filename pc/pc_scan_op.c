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
//add, ld
/*
void	pc_scan_op(t_cycle *cyc, t_pc *pc)
{
	t_pc	*tmp;
	t_mem	front[REG_SIZE];
	t_mem	back[REG_SIZE];

	tmp = pc;
	while (tmp)
	{
		tmp->i = MEM(tmp->i);
		if (tmp->wait < 0)
		{
			//wait = get data from op
			if (REG(cyc->mem[0][tmp->i].byte))
			{
				tmp->wait = WAIT_MOD(cyc->mem[0][tmp->i].byte) - 1;
			}
			//if wait == -1
			else
			{
				//increase position
				tmp->i = MEM(tmp->i + 1);
			}
		}
		else if (tmp->wait - 1 > 0)
		{
			tmp->wait--;
		}
		else
		{
			cw_memcp(front, &cyc->mem[0][0], REG_SIZE);
			cw_memcp(back, &cyc->mem[0][MEM_SIZE], REG_SIZE);
			if (REG(cyc->mem[0][tmp->i].byte))
				g_op_fn[cyc->mem[0][tmp->i].byte](cyc, tmp);
			else
			{
				tmp->i = MEM(tmp->i + 1);
				tmp->wait = -1;
			}
			if (ft_memcmp(front, &cyc->mem[0][0], sizeof(front)))
				cw_memcp(&cyc->mem[0][MEM_SIZE], &cyc->mem[0][0], REG_SIZE);
			if (ft_memcmp(back, &cyc->mem[0][MEM_SIZE], sizeof(back)))
				cw_memcp(&cyc->mem[0][0], &cyc->mem[0][MEM_SIZE], REG_SIZE);
			if (REG(cyc->mem[0][MEM(tmp->i)].byte))
				tmp->wait = WAIT_MOD(cyc->mem[0][MEM(tmp->i)].byte);
		}
		tmp->i = MEM(tmp->i);
		cyc->mem[0][tmp->i].active = (cyc->mem[0][tmp->i].active == 0) ? 1 : cyc->mem[0][tmp->i].active;
		tmp = tmp->next;
	}
}
*/

void	pc_scan_op(t_cycle *info, t_pc *pc)
{
	//ft_printf("at mem[%d] (%.2x) for %d more cycles\n", pc->i, info->mem[0][pc->i], pc->wait);
	t_pc	*tmp;
	t_mem	front[REG_SIZE];
	t_mem	back[REG_SIZE];

	tmp = pc;
	while (tmp)
	{
		//if (info->cycle == 8622 && tmp->i == 162)
			//tmp->wait -= 2;
		tmp->wait--;
		tmp->i %= MEM_SIZE; //GOT RID OF BUFFER OVERFLOW ON WRAPAROUND BUT SHOULD THIS BE THE FIX???
		if (!REG(info->mem[0][tmp->i].byte))// < 1 || info->mem[0][tmp->i].byte > 16)
		{
			tmp->i = MEM(tmp->i + 1);
			tmp->wait = -1;
		}
		else if (REG(info->mem[0][tmp->i].byte) && !tmp->wait)
		{
			//ft_printf("Doing function, tmp->i = %d\n", tmp->i);
			cw_memcp(front, &info->mem[0][0], REG_SIZE);
			cw_memcp(back, &info->mem[0][MEM_SIZE], REG_SIZE);
			//ft_printf("%d\n", info->mem[0][tmp->i].byte);
			g_op_fn[info->mem[0][tmp->i].byte](info, tmp);
			if (ft_memcmp(front, &info->mem[0][0], sizeof(front)))
				cw_memcp(&info->mem[0][MEM_SIZE], &info->mem[0][0], REG_SIZE);
			if (ft_memcmp(back, &info->mem[0][MEM_SIZE], sizeof(back)))
				cw_memcp(&info->mem[0][0], &info->mem[0][MEM_SIZE], REG_SIZE);
			if (REG(info->mem[0][tmp->i].byte)) 
				tmp->wait = WAIT_MOD(info->mem[0][tmp->i].byte);
			else
			{
		//		tmp->i = MEM(tmp->i + 1);
				tmp->wait = -1;
			}
		}
		if (tmp->wait < 0 && REG(info->mem[0][tmp->i].byte))
		{
			tmp->wait = WAIT_MOD(info->mem[0][tmp->i].byte);
			//tmp->i = MEM(tmp->i + 1);

		}
		info->mem[0][tmp->i].active = (info->mem[0][tmp->i].active == 0) ? 1 : info->mem[0][tmp->i].active;
		tmp = tmp->next;
	}
}
//Gagnant Notes: live ld add sub zjmp sti fork
