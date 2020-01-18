/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:31:51 by jochang           #+#    #+#             */
/*   Updated: 2019/02/21 17:35:12 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"
#include "../inc/gui.h"

static int	live_sum(uint32_t p[MAX_PLAYERS])
{
	uint32_t	total;
	uint32_t	i;

	total = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
		total += p[i];
	return (total);
}

static void	set_delay(uint32_t w)
{
	static clock_t	prev;
	clock_t	now;
	clock_t	diff;

	now = clock();
	diff = now - prev;
	if (diff < w)
		usleep(w - diff);
	prev = now;
}

static void	stepper(t_ncrs *ncrs, t_cycle *cycle, t_head *champ, t_flag *flag)
{
	int32_t		step;

	step = 0;
	while (step++ < cycle->die)
	{
		pc_scan_op(cycle, g_head);
		if (flag->n)
			update_gui(ncrs, cycle, champ, flag);
		cycle->cycle++;
		if (flag->w)
			set_delay(flag->w);
		if ((uint32_t)cycle->cycle == flag->d)
		{
			if(flag->v)
				cw_dump_pcs();
			cw_dump_mem(cycle, -1, -1);
		}
		if (flag->b)
			verify_cycle_bytes(cycle, (cycle->verification_bytestring));
	}
}

static int	kill_count(uint32_t kill, uint32_t total, t_cycle *cycle)
{
	if (total >= NBR_LIVE)
	{
		kill = 0;
		cycle->die -= CYCLE_DELTA;
	}
	else
		kill++;
	if (kill == MAX_CHECKS)
	{
		kill = 0;
		cycle->die -= CYCLE_DELTA;
	}
	return (kill);
}

int		init_env(t_cycle *info, t_head champ[MAX_PLAYERS], t_flag *flag)
{
	uint32_t	total;
	uint32_t	kill;
	t_ncrs		*ncrs;

	kill = 0;
	cw_memcp(&info->mem[0][MEM_SIZE], &info->mem[0][0], REG_SIZE);
	if (flag->n)
		ncrs = init_gui(info, champ, flag);
	while (info->die > 0)
	{
		stepper(ncrs, info, champ, flag);
		BREAK_CHECK(!g_head);
		total = live_sum(info->pcount);
		ft_memset(&info->pcount, 0, sizeof(info->pcount));
		pc_scan_rem(&g_head, info);
		BREAK_CHECK(!g_head);
		kill = kill_count(kill, total, info);
	}
	if (g_head)
		pc_free(g_head);
	if (flag->n)
		delete_gui(ncrs);
	int winner = -1;
	for(int i = 0; i < MAX_PLAYERS; ++i)
		if (info->last == champ[i].pnum)
			winner = i;
	//return (info->last);
	return (winner);
}
