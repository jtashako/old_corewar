/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtashako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:48:30 by jtashako          #+#    #+#             */
/*   Updated: 2019/03/11 22:48:49 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_strccpy(char *dst, const char *src, char c)
{
	int		i;

	i = -1;
	while (src[++i] && (src[i] != c))
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

static void	new_cor(char *fn, t_header s, t_byte file)
{
	char	*cor;
	int		fd;

	cor = ft_strnew(ft_strlen(fn) + 2);
	cor = ft_strccpy(cor, fn, '.');
	cor = ft_strcat(cor, ".cor");
	fd = open(cor, O_CREAT | O_RDWR | O_TRUNC, 0777);
	free(cor);
	write(fd, &s, HEADER_SIZE);
	write(fd, file.code, file.count);
	close(fd);
}

void		assembler(char *file)
{
	int			fd;
	t_header	h;
	t_byte		b;

	fd = open(file, O_RDONLY);
	if (fd == -1 || (read(fd, &fd, 0)) == -1)
		err_invfile(file);
	ft_memset(&h, 0, HEADER_SIZE);
	b = t_byte_init();
	if (get_header(&h, fd, file) && get_bytecode(&b, fd, file))
	{
		h.prog_size = END32(b.count);
		new_cor(file, h, b);
		t_byte_free(&b);
	}
	close(fd);
}
