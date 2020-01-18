//Jo's test file

/* TO DO

	start norming functions
	repeated code in or/and/xor can be extracted to helpers
	find out which codes work and which do not
	find the segfault from last time
*/

#include "../inc/corewar.h"

int32_t	get_val(t_cyc *info, t_pc *pc)
{
	return (info->mem[0][MEM(pc->i + IDX(info->mem[0][MEM(pc->i + 2)].byte))].byte);
}

void	op_and(t_cyc *info, t_pc *pc)
{
	int32_t	a;
	int32_t	b;
	int32_t	c;
	int16_t	loc;

	a = get_val(info, pc);
	pc->i++;
	b = get_val(info, pc);
	pc->i++;
	c = a & b;
	loc = acb_len(info->mem[0][MEM(pc->i + 1)].byte);
	pc->r[info->mem[0][MEM(pc->i + loc - 1)].byte] = c;
	pc->i++;
	pc->carry = c ? 0 : 1;
}


void	op_and(t_cyc *info, t_pc *pc)
{
	int32_t	d1;
	int32_t	d2;
	int16_t	loc;
	uint8_t	acb;

	d1 = 0;
	d2 = 0;
	acb = info->mem[0][MEM(pc->i + 1)].byte;
	//Gett first value
	if ((acb >> 6) == REG_CODE)
		ft_memrcpy(&d1, &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE);
	else if ((acb >> 6) == IND_CODE)
	{
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		cw_memren(&d1, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if ((acb >> 6) == DIR_CODE)
		cw_memren(&d1, &info->mem[0][MEM(pc->i + 2)], DIR_SIZE);
	else
	{
		pc->i++;
		return ;
	}
	//get second value
	if (((acb >> 4) & 3) == REG_CODE)
		ft_memrcpy(&d2, &pc->r[info->mem[0][MEM(pc->i + ACB_ARG(acb >> 6))].byte], REG_SIZE);
	else if (((acb >> 4) & 3) == IND_CODE)
	{
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 1 + ACB_ARG(acb >> 6))], IND_SIZE);
		cw_memren(&d2, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if (((acb >> 4) & 3) == DIR_CODE)
		cw_memren(&d2, &info->mem[0][MEM(pc->i + 1 + ACB_ARG(acb >> 6))], DIR_SIZE);
	else
	{
		pc->i++;
		return ;
	}
	//etc
	loc = acb_len(acb, bool);
	if (REG(info->mem[0][MEM(pc->i + loc - 1)].byte))
		pc->r[info->mem[0][MEM(pc->i + loc - 1)].byte] = d1 & d2;
	else
	{
		pc->i++;
		return ;
	}
	pc->carry = (d1 & d2) ? 0 : 1;
	pc->i += loc;
}