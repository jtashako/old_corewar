/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                         	 :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: jtashako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:03:54 by jtashako          #+#    #+#             */
/*   Updated: 2019/02/22 13:36:50 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

//static const char *hex = "0123456789abcdef";
/*
static	void	cw_dump_pc(t_pc *pc)
{
	(void) pc;
}
*/
/*
static	char	*ft_strjoinfree(char *s1, char *s2)
{
	char *ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ret == NULL)
		return (NULL);
	ret[0] = '\0';
	ret = ft_strcat(ret, s1);
	ret = ft_strcat(ret, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (ret);
}
*/

void	cw_dump_mem(t_cycle *info, int erow, int ecol)
{
	int     first;
	int	col;
	int	row;
	int	i;
	const char *hex = "0123456789abcdef";

	first = 1;
	col = 0;
	row = 0;
	i = 0;
	while (row < MEM_HEIGHT)
	{
		if (!first)
			ft_printf(" ");
		else
		{
			ft_printf("0x%c", hex[col / 4096 % 16]);
			ft_printf("%c", hex[col / 256 % 16]);
			ft_printf("%c%c : ", hex[col / 16  % 16], hex[col % 16]);
		}
		first = 0;
		if (row == erow && col == ecol)
		{
			ft_printf("\033[93m%c", hex[(info->mem[0][i].byte / 16) % 16]);
			ft_printf("\033[93m%c", hex[info->mem[0][i].byte % 16]);
			ft_printf("\033[0m");
		}
		else 
		{
			ft_printf("%c", hex[(info->mem[0][i].byte / 16) % 16]);
			ft_printf("%c", hex[info->mem[0][i].byte % 16]);
		}
		if (!((col++ + 1) % MEM_WIDTH))
		{
			first = 1;
			++row;
			ft_printf("\n");
		}
		++i;
	}
	exit(0);
}

void	cw_dump_pcs(void)
{
	t_pc	*head;
	int		pc_num;
	int		first;
	int		i;

	pc_num = 0;
	head = g_head;
	while(head)
	{
		ft_printf("\n");
		ft_printf("PC #%i : [Registers: ", pc_num++);
		first = 1;
		i = 0;
		while(i < REG_NUMBER + 1)
		{
			if (!first)
				ft_printf(", ");
			first = 0;
			ft_printf("%8x", head->r[i++]);
		}
		ft_printf("]\t[ i: %#04x(%i), carry: %i, alive: %i, wait: %i]\n", 
				  head->i, head->i, head->carry, head->alive, head->wait);
		head = head->next;
	}
	ft_printf("\n");
}

/*
char	*read_bytestring(void)
{
	//static const int N = 4242424;
	static const int stack_limit = 7000000;
	int	fd;
	long long size;
	char	buf[stack_limit + 1];
	char	*fbuf;
	char	*oldbuf;

	fbuf = (char *)malloc(sizeof(90000000));
	oldbuf = fbuf;
	fd = open("debug/current.bytestring", O_RDONLY);
	if (fd == -1) //error
	{
		ft_printf("Unable to open debug/current.bytestring\n");
		exit(1);  //exit on error
	}
	//ft_printf("fd is %i\n", fd);

	size = read(fd, buf, 900000000UL);

	while ((size = read(fd, buf, stack_limit)))
	{
		buf[size] = '\0';
		fbuf = ft_strjoin(fbuf, buf); //may leak
		if (!oldbuf)
			free(oldbuf);
		oldbuf = fbuf;
	}
	return (fbuf);
}
*/

char	*read_bytestring(void)
{
	//static const int N = 4242424;
	static const int stack_limit = 7000000;
	int	fd;
	long long size;
	char	buf[stack_limit + 1];
	char	*fbuf;
	char	*oldbuf;

	fbuf = (char *)malloc(sizeof(char));
	oldbuf = fbuf;
	fd = open("debug/current.bytestring", O_RDONLY);
	if (fd == -1) //error
	{
		ft_printf("Unable to open debug/current.bytestring\n");
		exit(1);  //exit on error
	}
	//ft_printf("fd is %i\n", fd);

	while ((size = read(fd, buf, stack_limit)))
	{
		buf[size] = '\0';
		fbuf = ft_strjoin(fbuf, buf); //may leak
		if (!oldbuf)
			free(oldbuf);
		oldbuf = fbuf;
	}
	return (fbuf);
}

void	verify_cycle_bytes(t_cycle *info, char *bytestring)
{
	int	row;
	int col;
	const char *hex = "0123456789abcdef";
	//static int i = 0;
	static int i = MEM_SIZE; //our cycle is off by 1
	int	j = 0;
	char oct1;
	char oct2;
	char halfbyte1;
	char halfbyte2;

	row = 0;
	col = 0;
	while (row < MEM_HEIGHT)
	{
		if ((bytestring[2*i] == '\n') || (bytestring[2*i+1] == '\n') || info->cycle >= V_LIMIT)
		{
			ft_printf("Verification success: bytestring matches exactly with 42corewar\n");
			//ft_printf("cycle is %i\n", info->cycle);
			exit(0);
			return ;
		}
		oct1 = hex[info->mem[0][j].byte / 16 % 16];
		oct2 = hex[info->mem[0][j].byte % 16];
		halfbyte1 = bytestring[2*i];
		halfbyte2 = bytestring[2*i+1];
		//ft_printf("%c %c %c %c\n", oct1, halfbyte1, oct2, halfbyte2);
		if (oct1 != halfbyte1)
		{
			ft_printf("Verification mismatch at: Cycle: %i, Row: %#04x(%i), Col: %i\n",
					info->cycle, row * 4 * 16, row, col % MEM_WIDTH);
					//info->cycle, row, col % MEM_WIDTH);
			ft_printf("byte string first nibble is %c.. mem is %c\n", halfbyte1, 
					hex[info->mem[0][j].byte / 16 % 16]);
			ft_printf("\n");
			cw_dump_pcs();
			cw_dump_mem(info, row, col);
		}
		if (oct2 != halfbyte2)
		{
			ft_printf("Verification mismatch at: Cycle: %i, Row: %#04x(%i), Col: %i\n",
					info->cycle, row * 4 * 16, row, col % MEM_WIDTH);
			ft_printf("byte string second nibble is %c.. mem is %c\n", halfbyte2, 
					hex[info->mem[0][j].byte % 16]);
			ft_printf("\n");
			cw_dump_pcs();
			cw_dump_mem(info, row, col);
		}

		if (!((col++ + 1) % MEM_WIDTH))
			++row;
		++i;
		++j;
	}
}
