/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtashako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:41:37 by jtashako          #+#    #+#             */
/*   Updated: 2019/03/12 17:09:55 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		free_line(char **coms, char **args)
{
	int i;

	if (coms)
	{
		i = -1;
		while (coms[++i])
			free(coms[i]);
		free(coms);
	}
	if (args)
	{
		i = -1;
		while (args[++i])
			free(args[i]);
		free(args);
	}
}

static void		acb_byte(int i, char **args, int lc, uint8_t *byte)
{
	int	a;

	a = 0;
	while (a < g_op_tab[i].argc)
	{
		if (ft_strchr("-0123456789:", args[a][0]) &&
			g_op_tab[i].types[a] & T_IND)
			*byte |= (IND_CODE << (6 - (a++ << 1)));
		else if (args[a][0] == 'r' && g_op_tab[i].types[a] & T_REG)
			*byte |= (REG_CODE << (6 - (a++ << 1)));
		else if (args[a][0] == '%' && g_op_tab[i].types[a] & T_DIR)
			*byte |= (DIR_CODE << (6 - (a++ << 1)));
		else
			err_invarg(args[a], lc);
	}
	if (args[a])
		err_invarg(args[a], lc);
}

static t_byte	arg_bytes(int i, char **args, int lc, uint8_t acb)
{
	t_byte		prm;
	int			a;
	int			n;

	n = 0;
	prm = t_byte_init();
	if (g_op_tab[i].acb == 0)
		return (arg_no_acb(i, args[0], lc, prm));
	a = -1;
	while (args[++a])
	{
		(a > g_op_tab[i].argc) ? err_invarg(args[a], lc) : 0;
		if (ft_strchr(args[a], ':'))
			prm = arg_label(prm, args[a], n, lc);
		else if (ARG_CHECK == REG_CODE)
			prm = arg_reg(prm, args[a], lc);
		else if (ARG_CHECK == DIR_CODE && g_op_tab[i].flag2 == 1)
			prm = arg_ind(prm, &args[a][1], lc);
		else if (ARG_CHECK == DIR_CODE && g_op_tab[i].flag2 == 0)
			prm = arg_dir(prm, args[a], lc);
		else if (ARG_CHECK == IND_CODE)
			prm = arg_ind(prm, args[a], lc);
	}
	return (prm);
}

static int		get_bytes(t_byte *b, char **coms, char **args, int lc)
{
	t_byte		prm;
	int			i;
	int			n;

	n = 0;
	if (ft_strrchr(coms[n], LABEL_CHAR))
	{
		b->label = ft_strndup(coms[n], ft_strlen(coms[n]) - 1);
		n++;
	}
	i = -1;
	while (g_op_tab[++i].name)
		BREAK_CHECK(!(ft_strcmp(g_op_tab[i].name, coms[n])));
	if (!g_op_tab[i].name)
		err_invop(coms[n], lc);
	b->code = (uint8_t*)realloc(b->code, 2);
	b->code[b->count++] = (uint8_t)(g_op_tab[i].code & 0xff);
	if (g_op_tab[i].acb)
		acb_byte(i, args, lc, &(b->code[b->count++]));
	prm = arg_bytes(i, args, lc, b->code[b->count - 1]);
	t_byte_append(b, prm);
	label_append(b, prm);
	free_line(coms, args);
	t_byte_free(&prm);
	return (1);
}

int				parser(t_byte *b, char *line, int lc)
{
	char	**coms;
	char	**args;
	char	*cmt;
	int		i;

	args = NULL;
	if ((cmt = ft_strchr(line, COMMENT_CHAR)))
		*cmt = 0;
	cmt = ft_strtrim(line);
	if (!cmt[0])
		return (2);
	coms = ft_strsplitwsp(cmt);
	free(cmt);
	i = 0;
	while (coms[i])
		i++;
	if (--i > 0)
		args = ft_strsplit(coms[i], ',');
	return (get_bytes(b, coms, args, lc));
}
