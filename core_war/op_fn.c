/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:38:43 by jochang           #+#    #+#             */
/*   Updated: 2019/02/13 01:14:45 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

const t_fn	g_op_fn[] = {
	NULL,		// 0
	&op_live,	// 1
	&op_ld,		// 2 👊
	&op_st,		// 3
	&op_add,	// 4 👊
	&op_sub,	// 5
	&op_and,	// 6
	&op_or,		// 7
	&op_xor,	// 8
	&op_zjmp,	// 9
	&op_ldi,	// a
	&op_sti,	// b
	&op_fork,	// c
	&op_lld,	// d
	&op_lldi,	// e
	&op_lfork,	// f
	&op_aff		// 10
};
