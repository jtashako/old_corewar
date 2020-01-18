/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:37:06 by jochang           #+#    #+#             */
/*   Updated: 2019/03/11 22:47:37 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	int		i;

	err_nofile("asm", ac);
	i = 0;
	while (++i < ac)
	{
		if (valid_extension(av[i], "s"))
			assembler(av[i]);
		else if (valid_extension(av[i], "cor"))
			ft_printf("Disassembler not implemented\n");
		else
			err_invfile(av[1]);
	}
	return (0);
}
