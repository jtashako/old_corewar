/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 09:51:24 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/25 19:35:59 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(const int fd, char **line)
{
	static char	*s[FDS];
	char		pipe[BUFF_SIZE + 1];
	char		*place;
	int			x;

	if (fd < 0 || fd >= FDS || !line || (!((!s[fd]) ? (s[fd] = ft_strnew(0))
								: (s[fd]))) || ((x = read(fd, pipe, 0)) == -1))
		return (-1);
	while ((x = read(fd, pipe, BUFF_SIZE)) > 0)
	{
		pipe[x] = '\0';
		s[fd] = ft_strjoinfr(s[fd], pipe);
	}
	if (!(s[fd][0] == '\0'))
	{
		if (!(place = ft_strchr(s[fd], '\n')))
			place = ft_strnew(0);
		else if (!(*place = '\0'))
			place = ft_strdup(place + 1);
		(*line = ft_strdup(s[fd])) ? ft_strdel(&s[fd]) : 1;
		(s[fd] = ft_strdup(place)) ? (free(place)) : 1;
		return (1);
	}
	ft_strclr(*line);
	return (x);
}

// # define ERROR_CHECK(x) if (x) return (0)
// # define BREAK_CHECK(x) if (x) break ;

// //tmp, add to libft later
// static char	*ft_strccpy(char *dst, const char *src, char c)
// {
// 	int		i;

// 	i = -1;
// 	while (src[++i] && (src[i] != c))
// 		dst[i] = src[i];
// 	dst[i] = '\0';
// 	return (dst);
// }

// static t_list	*assign_save(t_list **save, int fd)
// {
// 	t_list	*tmp;

// 	tmp = *save;
// 	while (tmp)
// 	{
// 		if ((int)(tmp->content_size) == fd)
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	tmp = ft_lstnew("\0", 0);
// 	ft_lstadd(save, tmp);
// 	return (*save);
// }

// static void		cleanup(t_list *ptr)
// {
// 	char	*tmp;

// 	if ((tmp = ft_strchr(ptr->content, '\n')))
// 	{
// 		tmp = ft_strdup(tmp + 1);
// 		free(ptr->content);
// 		ptr->content = tmp;
// 	}
// 	else
// 		ft_strclr(ptr->content);
// }

// int				get_next_line(const int fd, char **line)
// {
// 	char			buf[BUFF_SIZE + 1];
// 	char			*tmp;
// 	int				check;
// 	static t_list	*save;
// 	t_list			*ptr;

// 	ERROR_CHECK(fd < 0 || line == NULL || read(fd, buf, 0) < 0);
// 	ptr = assign_save(&save, fd);
// 	while ((check = read(fd, buf, BUFF_SIZE)) > 0)
// 	{
// 		buf[check] = '\0';
// 		ERROR_CHECK(!(tmp = ft_strjoin(ptr->content, buf)));
// 		free(ptr->content);
// 		ptr->content = tmp;
// 		BREAK_CHECK((ft_strchr(ptr->content, '\n')));
// 	}
// 	if (!check && !ft_strlen(ptr->content))
// 	{
// 		ft_strclr(*line);
// 		return (0);
// 	}
// 	ERROR_CHECK(!(*line = ft_strnew(ft_strlen(ptr->content))));
// 	*line = ft_strccpy(*line, ptr->content, '\n');
// 	cleanup(ptr);
// 	return (1);
// }