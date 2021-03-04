/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microPaint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:55:18 by jvaquer           #+#    #+#             */
/*   Updated: 2021/03/04 17:03:13 by jvaquer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

void		ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

int		ft_error(int x)
{
	if (x == 1)
		ft_putstr("Error: argument");
	else if (x == 2)
		ft_putstr("Error: Operation file corrupted");
	return	1;
}

char	**ft_fill_tab(char **tab, FILE *fd)
{
	char	type;
	float	x;
	float	y;
	float	w;
	float	h;
	char	c;
	int		i;
	int		j;
	int		ret;

	ret = 1;
	while (ret != -1)
	{
		ret = fscanf(fd, "%c %f %f %f %f %c\n", &type, &x, &y, &w, &h, &c);
		if (ret == -1)
			break ;
		if (w <= 0.0 || h <= 0.0)
			return	NULL;
		if (type != 'r' && type != 'R')
			return NULL;
		i = 0;
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				if (type == 'R')
				{
					if (j >= x && j <= x + w &&
						i >= y && i <= y + h)
						tab[i][j] = c;
				}
				else if (type == 'r')
				{
					if (j - x < 1.0 || (x + w) - j < 1.0 ||
						i - y < 1.0 || (y + h) - i < 1.0)
						if (j >= x && j <= x + w &&
							i >= y && i <= y + h)
							tab[i][j] = c;
				}
				j++;
			}
			i++;
		}
		c = 0;
	}
	return tab;
}

int		main(int ac, char **av)
{
	if (ac != 2)
		return 	ft_error(1);

	char	**tab;
	FILE	*fd;
	int		w;
	int		h;
	char	bg;
	int		i;

	if (!(fd = fopen(av[1], "r")))
		return	ft_error(2);
	fscanf(fd, "%d %d %c\n", &w, &h, &bg);
	if (w < 0 || h < 0 || w > 300 || h > 300 || !bg)
		return	ft_error(2);
	if (!(tab = malloc(sizeof(char *) * (h + 1))))
		return	ft_error(2);
	tab[h] = 0;

	i = 0;
	while (i < h)
	{
		if (!(tab[i] = malloc(sizeof(char) * (w + 1))))
			return	ft_error(2);
		int j = 0;
		while (j < h)
			tab[i][j++] = bg;
		tab[i][j] = 0;
		i++;
	}

	if (!(tab = ft_fill_tab(tab, fd)))
		return	ft_error(2);
	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i++]);
		ft_putstr("\n");
	}
	return	0;
}
