/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:04:24 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/20 17:04:26 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spaceskip(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

int		key_count(t_all *s)
{
	return (s->keys.w + s->keys.a + s->keys.s + s->keys.d);
}

double	check_angle(double angle)
{
	if (angle >= 360)
		return (angle - 360);
	if (angle < 0)
		return (angle + 360);
	return (angle);
}

short	is_in_map(int x, int y, t_map map)
{
	return (!(x < 0 || x >= map.w * BLOCK || y < 0 || y >= map.h * BLOCK));
}

int		map_pos(t_hit *hit, t_all *s)
{
	return ((int)(hit->y / BLOCK) * s->map.w + (int)(hit->x / BLOCK));
}
