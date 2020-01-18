/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:00:29 by jochang           #+#    #+#             */
/*   Updated: 2019/03/13 15:28:20 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <curses.h>
# include <time.h>
# include "op.h"
# include "err.h"
# include "../libft/libft.h"

/*
** Macros
*/

# define MEM(x) (((x) < 0) ? (MEM_SIZE + ((x) % MEM_SIZE)) : ((x) % MEM_SIZE))
//# define MEM(x) (((x) + MEM_SIZE) % MEM_SIZE)
# define IDX(x) ((x) % IDX_MOD)

// for pc_scan_op && pc_new
# define ARR -1, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2
# define WAIT_MOD(x) (uint16_t[]){ARR}[(x)]

# define ACB_ARG(x)		((int[]){0, 1, 2, 4}[x]) //(((x) == 3) ? 4 : (x))
# define ACB_ARG_1(x)	((int[]){0, 1, 2, 2}[x])
# define REG(r)			((r) > 0 && (r) <= REG_NUMBER)

# define TEA //g_time = clock()
# define TIME(s) //ft_printf("%s: %8lu\n", (s), clock() - g_time)

# define FLASH_LEN 50

# define MAX_DUMP_CYCLES 1000
# define MEM_WIDTH 64
# define MEM_HEIGHT 64
# define MEM_SIZE		(MEM_HEIGHT * MEM_WIDTH)
# define IDX_MOD		(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE	(MEM_SIZE / 6)

# define BREAK_CHECK(x) if (x) break

/*
** Structs
*/

typedef struct		s_mem
{
	uint8_t			byte; // content
	int				pnum; // pnum last modified
	uint8_t			timer; // decrement each cycle after mem modification
	uint16_t		active;
}					t_mem;

void				cw_memw(t_mem *mem, void *src, size_t n, int pnum);
void				cw_memr(void *dst, t_mem *mem, size_t n);
void				cw_memwen(t_mem *mem, void *src, size_t n, int pnum);
void				cw_memren(void *dst, t_mem *mem, size_t n);
void				cw_memcp(t_mem *dst, t_mem *src, size_t n);

/*
** Mem struct for array above, all stuff here for findability, needs organizing touch.
*/

typedef struct		s_flag
{
	uint8_t			p; //SOMETHING
	uint8_t			b; //verify bytestring 
	uint8_t			n; //ncurses visualizer
	uint8_t			s; //debug mode
	uint32_t		d; //dump memory
	uint8_t			v; //verbosity (combine flag with flags: "d")
	uint8_t			h; //hidden values, visualizer only
	uint32_t		w; //wait
}					t_flag;

typedef struct		s_head
{
	int				pnum;
	int				live;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	int				size;
	uint8_t			code[CHAMP_MAX_SIZE];
}					t_head;

typedef struct		s_pc
{
	uint16_t		i; //step counter for r
	int				r[REG_NUMBER + 1];
	uint8_t			carry;
	uint16_t		alive;
	int16_t			wait;
	struct s_pc		*next;
	struct s_pc		*prev;
}					t_pc;

typedef struct		s_cycle
{
	int32_t			cycle;
	//int32_t			last;
	int16_t			last;
	int32_t			die;
	uint32_t		breakdown[2];
	uint8_t			num_champs;
	uint32_t		last_live[MAX_PLAYERS];
	uint32_t		current_live[MAX_PLAYERS];
	uint32_t		prev_live[MAX_PLAYERS];
	uint32_t		pcount[MAX_PLAYERS];
	uint32_t		pc_info[MAX_PLAYERS];
	char			*verification_bytestring;
	t_mem			**mem;
}					t_cycle;

/*
** Dispatch Array
*/

void				op_live(t_cycle *info, t_pc *pc);
void				op_ld(t_cycle *info, t_pc *pc);
void				op_st(t_cycle *info, t_pc *pc);
void				op_add(t_cycle *info, t_pc *pc);
void				op_sub(t_cycle *info, t_pc *pc);
void				op_and(t_cycle *info, t_pc *pc);
void				op_or(t_cycle *info, t_pc *pc);
void				op_xor(t_cycle *info, t_pc *pc);
void				op_zjmp(t_cycle *info, t_pc *pc);
void				op_ldi(t_cycle *info, t_pc *pc);
void				op_sti(t_cycle *info, t_pc *pc);
void				op_fork(t_cycle *info, t_pc *pc);
void				op_lld(t_cycle *info, t_pc *pc);
void				op_lldi(t_cycle *info, t_pc *pc);
void				op_lfork(t_cycle *info, t_pc *pc);
void				op_aff(t_cycle *info, t_pc *pc);

typedef void		(*t_fn)(t_cycle *, t_pc *);
extern const t_fn	g_op_fn[];

/*
** Globals
*/

clock_t				g_time;
t_pc				*g_head;

/*
** Functions
*/

t_flag				ft_setopt(int ac, char **av);
t_head				parse_file(char *cor);
void				init_vm(t_head champ[MAX_PLAYERS], t_flag flag);
int					init_env(t_cycle *info, t_head champ[MAX_PLAYERS], t_flag *flag);

uint16_t			acb_len(uint8_t acb, bool last_field);
void				ft_memfree(uint8_t **m, size_t n);
void				ft_memrcpy(void *dst, void *src, size_t n);

void				display(t_cycle *info, t_head champ[MAX_PLAYERS], t_flag flag);

/*
** Util
*/

void				pc_app(t_pc **lst, t_pc *node);
void				pc_free(t_pc *pc);
t_pc				*pc_new(uint32_t pnum, uint16_t loc, uint8_t op);
void				pc_rem_head(t_pc **pc);
void				pc_rem(t_pc **rm);
void				pc_scan_rem(t_pc **pc, t_cycle *info);
void				pc_scan_op(t_cycle *info, t_pc *pc);

/*
** Debug
*/
void				cw_dump_mem(t_cycle *info, int erow, int ecol);
void				cw_dump_pcs(void);
char				*read_bytestring(void);
void				verify_cycle_bytes(t_cycle *info, char *bytestring);

#endif
