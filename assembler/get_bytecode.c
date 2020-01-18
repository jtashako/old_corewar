/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bytecode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 23:50:27 by jochang           #+#    #+#             */
/*   Updated: 2019/03/11 22:34:05 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_bytecode(t_byte *f, int fd, char *file)
{
	char		*line;
	t_label		*l;
	t_byte		tmp;
	static int	lc;

	l = NULL;
	while (get_next_line(fd, &line))
	{
		lc++;
		tmp = t_byte_init();
		if (line[0] && !(parser(&tmp, line, lc)))
		{
			t_byte_free(&tmp);
			return (err_invheader(file, line));
		}
		tmp.code ? t_byte_append(f, tmp) : 0;
		tmp.code && tmp.l[0].name ? label_append(f, tmp) : 0;
		l = tmp.label ? label_add(tmp, *f, l) : l;
		t_byte_free(&tmp);
		free(line);
	}
	f->code = label_fill(*f, l);
	return (1);
}
