/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:07 by jochang           #+#    #+#             */
/*   Updated: 2019/02/21 17:39:36 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_aff(t_cycle *info, t_pc *pc)
{
	uint32_t	chr;
	uint8_t		acb;

	acb = info->mem[0][MEM(pc->i + 1)].byte;
		//TMP HARDCODE SKIP AFF
	// pc->i = MEM(pc->i + 2);
	// return ;
	TEA;
	if (info->mem[0][MEM(pc->i + 1)].byte == 0x40)
	{
		chr = pc->r[info->mem[0][MEM(pc->i + 2)].byte];
		if (chr <= 0x7F)
			write(1, &chr, 1);
		else
			ft_putwchar(chr);
		pc->i = MEM(pc->i + 3);
		//pc->i = MEM(pc->i + 2);
	}
	else
		pc->i = MEM(pc->i + 2);
	TIME("op_aff\t");
}
