/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:06:50 by jochang           #+#    #+#             */
/*   Updated: 2019/02/21 17:36:02 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"
#include <stdio.h>

static t_cycle	init_t_cycle(t_mem **mem, int num_champs)
{
	t_cycle	info;
	int		i;

	ft_bzero(&info, sizeof(info));
	i = 0;
	while (i < num_champs)
		info.pc_info[i++] = 1;
	info.die = CYCLE_TO_DIE;
	info.num_champs = num_champs;
	info.mem = mem;
	return (info);
}

static void	init_proc(t_mem *mem, t_head champ[MAX_PLAYERS], t_flag flag)
{
	t_cycle	info;
	t_pc	*pc;
	int		i;
	int		winner;
	int		n;

	n = 0;
	while (n < MAX_PLAYERS && champ[n].pnum)
		n++;
	pc = pc_new(champ[0].pnum, 0, mem[0].byte);
	i = 0;
	while (++i < n)
		pc_app(&pc,
		pc_new(champ[i].pnum, MEM_SIZE / n * i, mem[MEM_SIZE / n * i].byte));
	info = init_t_cycle(&mem, n);
	if (flag.b)
		info.verification_bytestring = read_bytestring();
	g_head = pc;
	winner = init_env(&info, champ, &flag);

	ft_printf("Fighter #%i : (\"%s\") has won !\n", winner + 1, champ[winner].comment);
	// (winner = init_env(&info, champ, &flag)) ?
	// printf("Player %d (%s) won\n", winner, champ[-winner - 1].name) :
	// printf("There has been a tie!\n");
}

void	init_vm(t_head c[MAX_PLAYERS], t_flag flag)
{
	t_mem		*mem;
	int			i;
	int			n;

	mem = ft_memalloc(sizeof(*mem) * (MEM_SIZE + 4));
	n = 0;
	while (n < MAX_PLAYERS && c[n].pnum)
	{
		ft_printf("Fighter #%d: %s (\"%s\"), at %d bytes long!\n",
		n + 1, c[n].name, c[n].comment, c[n].size);
		n++;
	}
	i = -1;
	while (++i < n)
		cw_memw(&mem[MEM_SIZE / n * i], c[i].code, c[i].size, -c[i].pnum);
	init_proc(mem, c, flag);
}
