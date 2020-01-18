/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 00:36:51 by jochang           #+#    #+#             */
/*   Updated: 2019/03/11 22:14:59 by jtashako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_name(char str[], int fd, char *file)
{
	char	*line;
	char	*dq;
	int		i;

	ZERO_CHECK(!(get_next_line(fd, &line)));
	if (!ft_strnequ(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) ||
		!(dq = ft_strchr(line, '"')))
		return (err_invheader(file, line));
	dq++;
	i = -1;
	while (dq[++i] && dq[i] != '"' && i < PROG_NAME_LENGTH)
		str[i] = dq[i];
	if (dq[i] != '"')
		return (err_invheader(file, line));
	free(line);
	return (1);
}

static int	get_comment(char str[], int fd, char *file)
{
	char	*line;
	char	*dq;
	int		i;

	ZERO_CHECK(!(get_next_line(fd, &line)));
	if (!ft_strnequ(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) ||
		!(dq = ft_strchr(line, '"')))
		return (err_invheader(file, line));
	dq++;
	i = -1;
	while (dq[++i] && dq[i] != '"' && i < COMMENT_LENGTH)
		str[i] = dq[i];
	if (dq[i] != '"')
		return (err_invheader(file, line));
	free(line);
	return (1);
}

int			get_header(t_header *h, int fd, char *file)
{
	ZERO_CHECK(!(get_name(h->prog_name, fd, file)));
	ZERO_CHECK(!(get_comment(h->comment, fd, file)));
	h->magic = COREWAR_EXEC_MAGIC;
	h->magic = END32(h->magic);
	h->prog_size = 0;
	h->prog_size = END32(h->prog_size);
	return (1);
}
