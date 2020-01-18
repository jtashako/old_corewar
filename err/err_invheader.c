/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_invheader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 23:52:11 by jochang           #+#    #+#             */
/*   Updated: 2018/09/23 23:52:13 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err.h"

int	err_invheader(char *file, char *line)
{
	if (line)
		free(line);
	ft_printf("Error: invalid header in %s\n", file);
	return (0);
}
