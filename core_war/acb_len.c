/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acb_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 19:43:25 by smonroe           #+#    #+#             */
/*   Updated: 2019/05/04 00:33:16 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

inline uint16_t	acb_len(uint8_t acb, bool last_field)
{
	//TEA
	uint16_t	len;
	/*
	static const uint16_t l[] = {0, 1, 2, 4, 0, 1, 2, 2};
	len = l[2 * last_field + acb >> 6] + l[2 * last_field + (acb >> 4) & 3] + l[2 * last_field + (acb >> 2) & 3] + 2;
	*/
	static const uint16_t l[] = {0, 1, 4, 2};
	static const uint16_t l2[] = {0, 1, 2, 2};

	if (!last_field)
		len = l[acb >> 6] + l[(acb >> 4) & 3] + l[(acb >> 2) & 3] + 2;
	else
		len = l2[acb >> 6] + l2[(acb >> 4) & 3] + l2[(acb >> 2) & 3] + 2;

/*	len = 2;
	len += (((acb >> 6) == 3) ? 4 : (acb >> 6));
	len += ((((acb >> 4) & 3) == 3) ? 4 : ((acb >> 4) & 3));
	len += ((((acb >> 2) & 3) == 3) ? 4 : ((acb >> 2) & 3));*/
	//TIME("acb_len\t")
	return (len);
}
