/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:44:39 by jochang           #+#    #+#             */
/*   Updated: 2019/02/18 01:26:32 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static t_flag init_flags(void)
{
	t_flag	flags;

	flags.b = 0;
	flags.p = 0;
	flags.n = 0;
	flags.d = 0;
	flags.s = 0;
	flags.h = 0;
	flags.v = 0;
	flags.w = 50;
	return (flags);
}

static t_flag	set_flags(char c, t_flag flags)
{
	flags.b = (c == 'b' ? 1 : flags.b);
	flags.p = (c == 'p' ? 1 : flags.p);
	flags.n = (c == 'n' ? 1 : flags.n);
	flags.s = (c == 's' ? 1 : flags.s);
	flags.d = (c == 'd' ? ft_atoi(g_optarg) : flags.d);
	flags.v = (c == 'v' ? 1 : flags.v);
	flags.h = (c == 'h' ? 1 : flags.h);
	flags.w = (c == 'w' ? ft_atoi(g_optarg) : flags.w);
	return (flags);
}

t_flag	ft_setopt(int ac, char **av)
{
	t_flag	flags;
	int8_t	opt;

	flags = init_flags();
	g_optind = 1;
	while ((opt = ft_getopt(ac, av, "bpnsd:vhw:")) != -1)
	{
		err_invflag(opt);
		flags = set_flags(opt, flags);
	}
	flags.w = (flags.w && flags.n) ? 1000000/flags.w : 0;
	return (flags);
}
