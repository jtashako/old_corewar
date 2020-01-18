/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:00:55 by jochang           #+#    #+#             */
/*   Updated: 2019/03/12 16:00:56 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		valid_extension(char *file, char *ext)
{
	int		len;

	len = ft_strlen(file) - ft_strlen(ext) - 1;
	if (len <= 0 || file[len] != '.')
		return (0);
	len++;
	return (ft_strequ(&file[len], ext));
}
