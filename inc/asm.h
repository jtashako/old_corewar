/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:32:10 by jochang           #+#    #+#             */
/*   Updated: 2019/01/02 09:32:55 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "err.h"
# include "libft.h"

#include <stdio.h>

# define HEADER_SIZE	PROG_NAME_LENGTH + COMMENT_LENGTH + 8
# define ZERO_CHECK(x)	if (x) return (0)
# define BREAK_CHECK(x) if (x) break ;
# define ARG_CHECK		(acb >> (6 - (a << 1)) & 0x3)

typedef struct		s_label
{
	char			*name;
	uint16_t		loc;
	uint16_t		addr;
}					t_label;

typedef struct		s_byte
{
	char			*label;
	uint8_t			*code;
	uint16_t		count;
	t_label			*l;
}					t_byte;

typedef struct		s_header
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_op
{
	char			*name;
	int				argc;
	int				types[4];
	int				code;
	int				cycles;
	char			*desc;
	int				acb;
	int				flag2;
}					t_op;

extern const t_op	g_op_tab[17];

void		assembler(char *file);
int			valid_extension(char *file, char *ext);
int			get_header(t_header *h, int fd, char *file);
int			get_bytecode(t_byte *b, int fd, char *file);
int			parser(t_byte *b, char *line, int lc);

t_byte		t_byte_init(void);
void		t_byte_append(t_byte *org, t_byte app);
void		t_byte_free(t_byte *x);

t_byte		arg_ind(t_byte prm, char *arg, int lc);
t_byte		arg_dir(t_byte prm, char *arg, int lc);
t_byte		arg_reg(t_byte prm, char *arg, int lc);
t_byte		arg_label(t_byte prm, char *arg, int n, int lc);
t_byte		arg_no_acb(int i, char *arg, int lc, t_byte prm);

void		label_append(t_byte *org, t_byte app);
t_label		*label_add(t_byte b, t_byte f, t_label *l);
uint8_t		*label_fill(t_byte f, t_label *l);

#endif
