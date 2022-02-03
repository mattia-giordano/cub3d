/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:02:50 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:02:52 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pos(t_all *s)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (i++ < s->map.h)
	{
		j = 0;
		while (j++ < s->map.w)
		{
			c = s->map.ptr[(i - 1) * s->map.w + (j - 1)];
			if (ft_is_in_string(c, "NSEW"))
			{
				if (s->pl.x != 0 || s->pl.y != 0)
					return (-12);
				s->pl.x = (j - 1) * BLOCK + BLOCK / 2;
				s->pl.y = (i - 1) * BLOCK + BLOCK / 2;
				s->pl.angle = (c == 'N') ? 90.0 : 0.0;
				s->pl.angle = (c == 'S') ? 270.0 : s->pl.angle;
				s->pl.angle = (c == 'W') ? 180.0 : s->pl.angle;
			}
			s->map.spr += (c == '2') ? 1 : 0;
		}
	}
	return ((s->pl.x == 0 || s->pl.y == 0) ? -13 : 0);
}

int	check_if_closed(t_all *s)
{
	int i;
	int j;

	i = -1;
	while (++i < s->map.h)
	{
		j = -1;
		while (++j < s->map.w)
		{
			if (!ft_is_in_string(s->map.ptr[i * s->map.w + j], " 1"))
				if (((i - 1) == -1 ||
						s->map.ptr[(i - 1) * s->map.w + j] == ' ') ||
					((i + 1) == s->map.h ||
						s->map.ptr[(i + 1) * s->map.w + j] == ' ') ||
					((j - 1) == -1 ||
						s->map.ptr[i * s->map.w + (j - 1)] == ' ') ||
					((j + 1) == s->map.w ||
						s->map.ptr[i * s->map.w + (j + 1)] == ' '))
					return (-11);
		}
	}
	return (get_pos(s));
}

int	format_map(t_all *s, char *map_copy)
{
	int i;
	int j;
	int k;

	k = 0;
	if (!(s->map.ptr = malloc(s->map.w * s->map.h)))
		return (-8);
	i = 0;
	while (i < s->map.h)
	{
		j = 0;
		while (map_copy[k] != '\n')
			s->map.ptr[i * s->map.w + j++] = map_copy[k++];
		k++;
		while (j < s->map.w)
			s->map.ptr[i * s->map.w + j++] = ' ';
		i++;
	}
	free(map_copy);
	return (check_if_closed(s));
}

int	mapcheck(t_all *s)
{
	char	*map_copy;
	int		w;
	int		i;

	if (!s->map.ptr)
		return (my_strerror(-6));
	map_copy = ft_strdup(s->map.ptr);
	free(s->map.ptr);
	i = 0;
	w = 0;
	while (map_copy[i])
	{
		if (map_copy[i++] == '\n')
		{
			s->map.h++;
			if (w > s->map.w)
				s->map.w = w;
			w = -1;
		}
		w++;
	}
	i = format_map(s, map_copy);
	return ((i < 0) ? my_strerror(i) : 0);
}
