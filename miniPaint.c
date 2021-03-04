/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniPaint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:02:53 by jvaquer           #+#    #+#             */
/*   Updated: 2021/03/04 15:37:34 by jvaquer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_putstr(char *s)
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
		ft_putstr("Error: Arguments");
	if (x == 2)
		ft_putstr("Error: Operation file corrupted");
	return	1;
}

char	**ft_fill_circle(char **tab, FILE *fd)
{
	float	x;
	float	y;
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
			return	NULL;
		if (type != 'C' && type != 'c')
			return	NULL;
		i = 0;
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				float dist;
				dist = sqrt((x - j) * (x - j) + (y - i) * (y - i));
				if (type == 'C')
				{
					if (dist <= rad)
						tab[i][j] = c;
				}
				else if (type == 'c')
				{
					if (dist - rad < 0  && dist - rad > -1)
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
		return	(ft_error(1));
	
	char	**tab;
	FILE	*fd;
	int		i;
	int		w;
	int		h;
	char	bg;

	if (!(fd = fopen(av[1], "r")))
		return	(ft_error(2));
	fscanf(fd, "%d %d %c\n", &w, &h, &bg);
	if (w <= 0 || w > 300 || h > 300 || h <= 0 || !bg)
		return 	ft_error(2);
	if (!(tab = malloc(sizeof(char *) * (h + 1))))
		return	ft_error(2);
	tab[h] = NULL;

	i = 0;
	while (i < h)
	{
		if (!(tab[i] = malloc(sizeof(char) * (w + 1))))
			return	ft_error(2);
		int j = 0;
		while (j < w)
			tab[i][j++] = bg;
		tab[i][j] = 0;
		i++;
	}

	if (!(tab = ft_fill_circle(tab, fd)))
		return	ft_error(2);
	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i++]);
		ft_putstr("\n");
	}
	return 0;
}
