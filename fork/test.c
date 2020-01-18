/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:22:39 by smonroe           #+#    #+#             */
/*   Updated: 2019/02/22 13:13:15 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct		s_rgx
{
	int				c;
	struct s_rgx	**n;
}					t_rgx;

t_rgx	*newrgx(int c, int n)
{
	t_rgx *ret;
	int i;

	ret  = malloc(sizeof(*ret));
	ret->c = c;
	ret->n = malloc(sizeof(*(ret->n)) * ++n);
	i = -1;
	while (++i < n)
		ret->n[i] = 0;
	return (ret);
}

t_rgx	*buildrgx(void)
{
	t_rgx *root = newrgx('$', 9);
	root->n[7] = 0;
	root->n[8] = newrgx(0, 0);
	root->n[0] = newrgx('a', 3);
	root->n[0]->n[0] = newrgx('f', 1);
	root->n[0]->n[0]->n[0] = newrgx('f', 1);
	root->n[0]->n[0]->n[0]->n[0] = root->n[8];
	root->n[0]->n[1] = newrgx('n', 1);
	root->n[0]->n[1]->n[0] = newrgx('d', 1);
	root->n[0]->n[1]->n[0]->n[0] = root->n[8];
	root->n[0]->n[2] = newrgx('d', 1);
	root->n[0]->n[2]->n[0] = root->n[0]->n[1]->n[0];

	root->n[2] = newrgx('s', 2);
	root->n[2]->n[0] = newrgx('u', 1);
	root->n[2]->n[0]->n[0] = newrgx('b', 1);
	root->n[2]->n[0]->n[0]->n[0] = root->n[8];
	root->n[2]->n[1] = newrgx('t', 2);
	root->n[2]->n[1]->n[0] = newrgx('i', 1);
	root->n[2]->n[1]->n[0]->n[0] = root->n[8];
	root->n[2]->n[1]->n[1] = root->n[8];

	root->n[3] = newrgx('f', 1);
	root->n[3]->n[0] = newrgx('o', 1);
	root->n[3]->n[0]->n[0] = newrgx('r', 1);
	root->n[3]->n[0]->n[0]->n[0] = newrgx('k', 1);
	root->n[3]->n[0]->n[0]->n[0]->n[0] = root->n[8];

	root->n[1] = newrgx('l', 4);
	root->n[1]->n[0] = root->n[3];
	root->n[1]->n[1] = newrgx('d', 2);
	root->n[1]->n[1]->n[0] = newrgx('i', 1);
	root->n[1]->n[1]->n[0]->n[0] = root->n[8];
	root->n[1]->n[1]->n[1] = root->n[8];
	root->n[1]->n[2] = newrgx('l', 1);
	root->n[1]->n[2]->n[0] = root->n[1]->n[1];
	root->n[1]->n[3] = newrgx('i', 1);
	root->n[1]->n[3]->n[0] = newrgx('v', 1);
	root->n[1]->n[3]->n[0]->n[0] = newrgx('e', 1);
	root->n[1]->n[3]->n[0]->n[0]->n[0] = root->n[8];


	root->n[4] = newrgx('o', 1);
	root->n[4]->n[0] = newrgx('r', 1);
	root->n[4]->n[0]->n[0] = root->n[8];

	root->n[5] = newrgx('x', 1);
	root->n[5]->n[0] = root->n[4];

	root->n[6] = newrgx('z', 1);
	root->n[6]->n[0] = newrgx('j', 1);
	root->n[6]->n[0]->n[0] = newrgx('m', 1);
	root->n[6]->n[0]->n[0]->n[0] = newrgx('p', 1);
	root->n[6]->n[0]->n[0]->n[0]->n[0] = root->n[8];

	return (root);
}

int match(t_rgx* rgx, char *str)
{
	int i;

	if (!rgx || !str)
		return 0;
	if (rgx->c == 0)
		return 1;
	i = -1;
	while (rgx->n[++i])
		if (rgx->n[i]->c == *str)
			return match(rgx->n[i], str + 1);
	return 0;
}

void	run(char *s)
{
	static t_rgx *root;
	int fd;
	int ln;
	char *line;
	char *p;

	if (!root)
		root = buildrgx();
	if ((fd = open(s, O_RDONLY)) < 0)
		return ;
	ln = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ln++;
		if ((p = ft_strchr(line, '#')))
			*p = 0;
		p = ft_strtrim(line);
		if (!match(root, p))
			ft_printf("Error: line %d : %s\n", ln, line);
		free(p);
		free(line);
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
		run(av[1]);
	else
		ft_printf("\n");
	return 0;
}
