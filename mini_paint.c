/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:23:27 by jvaquer           #+#    #+#             */
/*   Updated: 2021/03/01 12:41:39 by jvaquer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

void	ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

int		ft_error()
{
	ft_putstr("Error: Operation file\n");
	return (1);
}

char	**ft_fill_circle(char **tab, FILE *fd)
{
	float	y;
	float	x;
	float	rad;
	char	type;
	char	c;
	int		ret;
	int		i;
	int		j;

	ret = 1;
	c = 0;
	while (ret != -1)
	{
		ret = fscanf(fd, "%c %f %f %f %c\n", &type, &x, &y, &rad, &c);
		if (ret == -1)
			break ;
		if (rad <= 0 || !c)
			return NULL;
		if (type != 'c' && type != 'C')
			return NULL;
		i = 0;
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				float res;
				res = sqrt((y - i) * (y - i) + (x - j) * (x - j));
				if (type == 'C')
				{
					if (res <= rad)
						tab[i][j] = c;
				}
				else if (type == 'c')
				{
					if (res - rad < 0 && res -rad > -1)
						tab[i][j] = c;
				}
					j++;
			}
			i++;
		}
		c = 0;
	}
	return	tab;
}

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}

	char	**tab;
	FILE	*fd;
	int		i;
	int		w;
	int		h;
	char	back;

	if (!(fd = fopen(av[1], "r")))
		return (ft_error());
	fscanf(fd, "%d %d %c\n", &w, &h, &back);
	if (w <= 0 || w > 300 || h > 300 || h <= 0 || !back)
		return (ft_error());
	if (!(tab = malloc(sizeof(char *) * (h + 1))))
		return (ft_error());
	tab[h] = NULL;
	i = 0;
	while (i < h)
	{
		if (!(tab[i] = malloc(sizeof(char) * w + 1)))
			return (ft_error());
		int k = 0;
		while (k < w)
			tab[i][k++] = back;
		tab[i][w] = 0;
		i++;
	}

	if (!(tab = ft_fill_circle(tab, fd)))
		return (ft_error());
	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i++]);
		ft_putstr("\n");
	}
	return	0;
}
