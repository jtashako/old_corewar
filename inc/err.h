/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:35:53 by jochang           #+#    #+#             */
/*   Updated: 2019/01/02 09:39:52 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include "libft.h"
# define RETURN_CHECK(x) if (x) return

void	err_nofile(char *prog, int n);
void	err_invfile(char *file);
int		err_invop(char *op, int l);
void	err_invarg(char *op, int l);
void	err_invflag(char c);
void	err_malloc(char *fun);
int		err_invheader(char *file, char *line);

#endif
