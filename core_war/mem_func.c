/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:32:30 by smonroe           #+#    #+#             */
/*   Updated: 2019/02/15 16:50:48 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

inline void	cw_memcp(t_mem *dst, t_mem *src, size_t n)
{
	int i;

	i = -1;
	while ((size_t)(++i) < n)
		dst[i] = src[i];
}

void	cw_memw(t_mem *mem, void *src, size_t n, int pnum)
{
	uint8_t *s;
	int i;

	s = src;
	i = -1;
	while ((size_t)(++i) < n)
	{
		mem[i].byte = s[i];
		mem[i].pnum = pnum;
		mem[i].timer = 0;
	}
	//temp solution for starting process active until i find out where its normally being set
	//mem[0].active = 1;
}

void	cw_memr(void *dst, t_mem *mem, size_t n)
{
	uint8_t	*d;
	int i;

	d = dst;
	i = -1;
	while ((size_t)(++i) < n)
		d[i] = mem[i].byte;
}

/*
** Below are same functions but endian reversed
*/

void	cw_memwen(t_mem *mem, void *src, size_t n, int pnum)
{
	uint8_t *s;
	int i;

	s = src;
	i = -1;
	while ((size_t)(++i) < n)
	{
		mem[i].byte = s[n - i - 1];
		mem[i].pnum = pnum;
		mem[i].timer = FLASH_LEN;
	}
}

void	cw_memren(void *dst, t_mem *mem, size_t n)
{
	uint8_t	*d;
	int i;

	d = dst;
	i = -1;
	while ((size_t)(++i) < n)
		d[i] = mem[n - i - 1].byte;
}

