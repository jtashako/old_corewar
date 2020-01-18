/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:24:55 by jochang           #+#    #+#             */
/*   Updated: 2019/02/12 22:24:56 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/splash_screen.h"

static void	p1(t_splash s, int ch)
{
	SN(1, "▄████████");
	SN(12, "▄██████▄");
	SN(24, "▄████████");
	SN(38, "▄████████");
	SN(49, "▄█");
	SN(56, "█▄");
	SN(63, "▄████████");
	SN(76, "▄████████");
	ch++;
	SN(0, "███");
	SN(7, "███");
	SN(11, "███");
	SN(18, "███");
	SN(24, "███");
	SN(31, "███");
	SN(37, "███");
	SN(44, "███");
	SN(48, "███");
	SN(56, "███");
	SN(62, "███");
	SN(69, "███");
	SN(75, "███");
	SN(82, "███");
}

static void	p2(t_splash s, int ch)
{
	SN(0, "███");
	SN(7, "█▀");
	SN(11, "███");
	SN(18, "███");
	SN(24, "███");
	SN(31, "███");
	SN(37, "███");
	SN(44, "█▀");
	SN(48, "███");
	SN(56, "███");
	SN(62, "███");
	SN(69, "███");
	SN(75, "███");
	SN(82, "███");
	ch++;
	SN(0, "███");
	SN(11, "███");
	SN(18, "███");
	SN(23, "▄███▄▄▄▄██▀");
	SN(36, "▄███▄▄▄");
	SN(48, "███");
	SN(56, "███");
	SN(62, "███");
	SN(69, "███");
	SN(74, "▄███▄▄▄▄██▀");
}

static void	p3(t_splash s, int ch)
{
	SN(0, "███");
	SN(11, "███");
	SN(18, "███");
	SN(22, "▀▀███▀▀▀▀▀");
	SN(35, "▀▀███▀▀▀");
	SN(48, "███");
	SN(56, "███");
	SN(60, "▀███████████");
	SN(73, "▀▀███▀▀▀▀▀");
	ch++;
	SN(0, "███");
	SN(7, "█▄");
	SN(11, "███");
	SN(18, "███");
	SN(22, "▀███████████");
	SN(37, "███");
	SN(44, "█▄");
	SN(48, "███");
	SN(56, "███");
	SN(62, "███");
	SN(69, "███");
	SN(73, "▀███████████");
}

static void	p4(t_splash s, int ch)
{
	SN(0, "███");
	SN(7, "███");
	SN(11, "███");
	SN(18, "███");
	SN(24, "███");
	SN(31, "███");
	SN(37, "███");
	SN(44, "███");
	SN(48, "███");
	SN(52, "▄█▄");
	SN(56, "███");
	SN(62, "███");
	SN(69, "███");
	SN(75, "███");
	SN(82, "███");
	ch++;
	SN(0, "████████▀");
	SN(12, "▀██████▀");
	SN(24, "███");
	SN(31, "███");
	SN(37, "██████████");
	SN(49, "▀███▀███▀");
	SN(62, "███");
	SN(69, "█▀");
	SN(75, "███");
}

void		splash_name(t_splash s)
{
	int	ch;

	ch = -5;
	wattron(s.win, COLOR_PAIR(1));
	p1(s, ch);
	ch += 2;
	p2(s, ch);
	ch += 2;
	p3(s, ch);
	ch += 2;
	p4(s, ch);
	ch++;
	SN(82, "███");
	ch++;
	SN(24, "███");
	SN(31, "███");
	SN(75, "███");
	SN(82, "███");
	wattroff(s.win, COLOR_PAIR(1));
}
